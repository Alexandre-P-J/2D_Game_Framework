#include "Game.h"
#include "Map.h"
#include "Camera.h"
#include <iostream>

Game::Game() {
	GameMap.Reload("Map.tmx");

	auto MainPlayer = std::make_shared<Player>();
	OBJList.push_back(MainPlayer);
	Players.push_back(MainPlayer);
}

std::shared_ptr<Player> Game::getPlayer(int id) {
	if (id < Players.size())
		return Players[id];
	return nullptr;
}

void Game::Update() {
	UpdateObjects();

	GameMap.Update();
}

void Game::UpdateObjects() {
	auto it = OBJList.begin();
	while (it != OBJList.end()) {
		if ((*it)->Update())
			++it;
		else
			it = OBJList.erase(it);
	}
}

std::pair<uint32_t,uint32_t> Game::getMapSize(const int z) const {
	return GameMap.getLevelSize(z);
}

std::pair<int,int> Game::getMapLevelsInterval() const {
	return std::make_pair(GameMap.getMinLevel(), GameMap.getMaxLevel());
}
