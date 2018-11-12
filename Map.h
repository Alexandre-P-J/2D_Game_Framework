#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include "RenderScheduler.h"
#include "Camera.h"
#include "ExtraTypes.h"

struct MapTile {
	SDL_Texture* Texture = nullptr;
	SDL_Rect SrcRect;
	unsigned char Behaviour; //<0>=block, <1>=editable?...
};

struct MapObject {
	unsigned int ID;
	Position Location;
	SDL_Texture* Texture;
	SDL_Rect SrcRect;
};

struct Level {
	unsigned int Width, Height;
	//std::vector<std::tuple<SDL_Texture*, int8_t, int8_t>> Tiles; //ptr,x,y
	std::vector<MapTile> Tiles;
	std::vector<MapObject> Objects;

};


class Map {

	std::vector<Level> Levels;
	int minLevel;

	public:
	Map();
	Map(const std::string& MapFile);
	void Reload(const std::string& MapFile);

	Level* getLevel (const int Level);

	void Update(const Camera& cam);
};
