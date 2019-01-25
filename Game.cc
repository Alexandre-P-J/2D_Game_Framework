#include "Game.h"
#include "Map.h"
#include "Camera.h"
#include <iostream>
#include <set>

GamePhysics::GamePhysics() {}
GamePhysics::GamePhysics(int minlevel, int Nlevels) :
	WorldPerLevel(Nlevels, b2Vec2(0, 0)), minlevel(minlevel) {}

void GamePhysics::Build(int minlevel, int Nlevels) {
	this->minlevel = minlevel;
	WorldPerLevel = std::vector<b2World>(Nlevels, b2Vec2(0, 0));
}
b2World& GamePhysics::operator[] (int x) {
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
		auto levelPtr = MapSnapshot.getLevel(i);
		for (auto obj : levelPtr->Objects) {
			auto Wptr = Object::create(obj.type, obj.ID); // added to the object map automatically
			auto Sptr = Wptr.lock(); // is valid, no check needed
			Position P = {obj.x, obj.y, i};
			Sptr->setPosition(P);
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
		if ((*it).second->Update())
			++it;
		else
			it = Objects.erase(it);
	}
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
				result.push_back(&WorkingMap[Z]);
				checkin.insert(Z);
			}
		}
	}
	return result;
}
