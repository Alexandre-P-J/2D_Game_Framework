#include "Game.h"
#include "Map.h"
#include "Camera.h"


Game::Game() {
	GameMap.Reload("Map.tmx");
}

std::vector<Player*>& Game::getPlayers() {
	return Players;
}

void Game::Update() {
	Position P = std::make_tuple(32,0,-1);
	Camera cam(P, 100, 100, 1);
	GameMap.Update(cam);
}
