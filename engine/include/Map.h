#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <utility>
#include "Camera.h"
#include "ExtraTypes.h"

struct MapTile {
	SDL_Texture* Texture = nullptr;
	SDL_Rect SrcRect;
};

struct MapObject {
	unsigned int ID;
	int x, y;
	std::string type;
};

struct Level {
	uint32_t Width, Height;
	std::vector<MapTile> Tiles;
	std::list<MapObject> Objects;

};


class Map {
		std::vector<Level> Levels;
		int minLevel = std::numeric_limits<int>::max();
	public:
		Map();
		Map(const std::string& MapFile);
		void Reload(const std::string& MapFile);

		void Update();

		std::pair<uint32_t,uint32_t> getLevelSize(int const LevelID) const;
		Level* getLevel (const int Level);
		bool LevelExists(const int Level);

		int getMinLevel() const;
		int getMaxLevel() const;
};
