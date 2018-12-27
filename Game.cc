#include "Game.h"
#include "Map.h"
#include "Camera.h"
#include "Input.h"
#include <iostream>

Game::Game() {
	GameMap.Reload("Map.tmx");

	auto MainPlayer = new Player();
	OBJList.push_back(MainPlayer);
	Players.push_back(MainPlayer);
}

Game::~Game() {
	for (auto OBJ : OBJList)
		delete OBJ;
	for (auto Player : Players)
		delete Player;
}

std::vector<Player*>& Game::getPlayers() {
	return Players;
}

void Game::Update() {
	UpdateObjects();

	GameMap.Update();
}

void Game::UpdateObjects() {
	auto it = OBJList.begin();
	while (it != OBJList.end()) {
		if (!((*it)->Update()))
			it = OBJList.erase(it);
		else
			++it;
	}
}

std::pair<uint32_t,uint32_t> Game::getMapSize(const int z) const {
	return GameMap.getLevelSize(z);
}
