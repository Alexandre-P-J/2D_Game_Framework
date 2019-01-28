#include "Game.h"
#include "Map.h"
#include "Camera.h"
#include <iostream>
#include <set>
#include "Box2D/Box2D.h"

GamePhysics::GamePhysics() {}
GamePhysics::GamePhysics(int minlevel, int Nlevels) :
	WorldPerLevel(Nlevels, nullptr), minlevel(minlevel) {
		for (int i = 0; i < Nlevels; ++i) {
			auto g = b2Vec2(0, 0);
			WorldPerLevel[i] = new b2World(g);
		}
	}

void GamePhysics::Build(int minlevel, int Nlevels) {
	this->minlevel = minlevel;
	WorldPerLevel = std::vector<b2World*>(Nlevels, nullptr);
	for (int i = 0; i < Nlevels; ++i) {
		auto g = b2Vec2(0, 0);
		WorldPerLevel[i] = new b2World(g);
	}
}
b2World* GamePhysics::operator[] (int x) {
	return WorldPerLevel[x-minlevel];
}

Game::Game() {
	MapSnapshot.Reload("Map.tmx");
	auto interval = getMapLevelsInterval();
	WorkingMap.Build(interval.first, interval.second - interval.first + 1);

}

void Game::MapSnapshotToWorkingMap() {
	auto interval = getMapLevelsInterval();
	for (int i = interval.first; i <= interval.second; ++i) {
		//Creating 4 invisible walls at the ends of the level
		auto worldPTR = getWorldFromLevel(i);
		auto MapSize = getMapSize(i);
		b2BodyDef BDefL;
		b2BodyDef BDefT;
		b2BodyDef BDefR;
		b2BodyDef BDefB;
		BDefL.position.Set(-16, MapSize.second/2);
		BDefT.position.Set(MapSize.first/2, -16);
		BDefR.position.Set(MapSize.first-16, MapSize.second/2);
		BDefB.position.Set(MapSize.first/2, MapSize.second-48);
		auto BodyL = worldPTR->CreateBody(&BDefL);
		auto BodyT = worldPTR->CreateBody(&BDefT);
		auto BodyR = worldPTR->CreateBody(&BDefR);
		auto BodyB = worldPTR->CreateBody(&BDefB);
		b2PolygonShape ShapeL;
		b2PolygonShape ShapeT;
		b2PolygonShape ShapeR;
		b2PolygonShape ShapeB;
		ShapeL.SetAsBox(16, MapSize.second/2);
		ShapeT.SetAsBox(MapSize.first/2, 16);
		ShapeR.SetAsBox(16, MapSize.second/2);
		ShapeB.SetAsBox(MapSize.first/2, 16);
		BodyL->CreateFixture(&ShapeL, 0);
		BodyT->CreateFixture(&ShapeT, 0);
		BodyR->CreateFixture(&ShapeR, 0);
		BodyB->CreateFixture(&ShapeB, 0);

		auto levelPtr = MapSnapshot.getLevel(i);
		for (auto obj : levelPtr->Objects) {
			Position P = {obj.x, obj.y, i};
			Object::create(obj.type, P, obj.ID);
		}
	}
}

std::weak_ptr<Object> Game::getPlayer(int id) {
	if (id < Players.size() && id >= 0)
		return Players[id];
	return std::weak_ptr<Object>();
}

void Game::Update() {
	UpdateObjects();
	MapSnapshot.Update();
}

void Game::UpdateObjects() {
	auto it = Objects.begin();
	while (it != Objects.end()) {
		if (it->second->Update())
			++it;
		else
			it = Objects.erase(it);
	}
}

b2World* Game::getWorldFromLevel(int z) {
	return WorkingMap[z];
}

std::pair<uint32_t,uint32_t> Game::getMapSize(const int z) const {
	return MapSnapshot.getLevelSize(z);
}

std::pair<int,int> Game::getMapLevelsInterval() const {
	return std::make_pair(MapSnapshot.getMinLevel(), MapSnapshot.getMaxLevel());
}

std::vector<b2World*> Game::getPhysicsToUpdate() {
	std::vector<b2World*> result;
	result.reserve(Players.size());
	std::set<int> checkin;
	for (auto player : Players) {
		auto sptr = player.lock();
		if (sptr) {
			int Z = std::get<2>(sptr->getPosition());
			if (checkin.find(Z) == checkin.end()) {
				result.push_back(WorkingMap[Z]);
				checkin.insert(Z);
			}
		}
	}
	return result;
}
