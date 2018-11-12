#pragma once
#include "Map.h"
#include "Player.h"
#include <vector>

class Game {
	Map GameMap;
	std::vector<Player*> Players;
	public:
		Game();
		std::vector<Player*>& getPlayers();
		void Update();
};
