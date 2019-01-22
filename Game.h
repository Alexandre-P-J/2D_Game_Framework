#pragma once
#include "Map.h"
#include "Player.h"
#include "ExtraTypes.h"
#include <vector>
#include <list>
#include "Object.h"
#include <memory>

class Game {
		Map GameMap;
		std::list<std::shared_ptr<Object>> OBJList;
		std::vector<std::shared_ptr<Player>> Players;

		void UpdateObjects();

	public:
		Game();

		void Update();

		std::shared_ptr<Player> getPlayer(int id);
		std::pair<uint32_t,uint32_t> getMapSize(const int z) const;
		std::pair<int,int> getMapLevelsInterval() const;
};
