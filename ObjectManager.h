#pragma once
#include <list>
#include "Object.h"
#include <memory>
#include "Player.h"

class ObjectManager {
	std::list<std::unique_ptr<Object>> L;
	bool HasPlayer = false;
	public:
		void Add(std::unique_ptr<Object>& Obj);
		void Run();
		void spawnPlayer();
		Player& getPlayer();
};
