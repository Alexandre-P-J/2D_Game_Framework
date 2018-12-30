#pragma once
#include "Map.h"
#include "Player.h"
#include "ExtraTypes.h"
#include <vector>
#include <list>
#include "Object.h"

class Game {
	Map GameMap;
	std::list<Object*> OBJList;
	std::vector<Player*> Players;

	void UpdateObjects();
	public:
		Game();
		~Game();

		void Update();

		Player* getPlayer(int id);

		std::pair<uint32_t,uint32_t> getMapSize(const int z) const;
		std::pair<int,int> getMapLevelsInterval();
};
