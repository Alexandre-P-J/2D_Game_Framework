#pragma once
#include "Map.h"
#include "Player.h"
#include "ExtraTypes.h"
#include <vector>
#include <list>
#include "Object.h"
#include <memory>
#include "Box2D/Box2D.h"
#include <cassert>

class GamePhysics {
	std::vector<b2World*> WorldPerLevel;
	std::vector<float*> TimeAcumulators;
	int minlevel;
public:
	GamePhysics();
	GamePhysics(int minlevel, int Nlevels);
	void Build(int minlevel, int Nlevels);
	b2World* operator[] (int x);
	float* TimeAcumulator (int x);
};

class Game {
		friend Object;

		Map MapSnapshot; // Copy more or less updated of the map file

		// Working Map information
		GamePhysics WorkingMap;
		std::map<int,std::shared_ptr<Object>> Objects; //<uuid, ptr>
		std::vector<std::weak_ptr<Object>> Players;

		void UpdateObjects();

	public:
		Game();

		void Update();
		std::vector<std::pair<b2World*,float*>> getPhysicsToUpdate();

		void MapSnapshotToWorkingMap();

		b2World* getWorldFromLevel(int z);
		std::weak_ptr<Object> getPlayer(int id);
		std::pair<uint32_t,uint32_t> getMapSize(const int z) const;
		std::pair<int,int> getMapLevelsInterval() const;
};
