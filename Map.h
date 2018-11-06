#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include "RenderScheduler.h"
#include "Camera.h"


struct Level {
	std::pair<int,int> Size;
	std::vector<int> Tiles;
	unsigned char Behaviour; //<0>=block, <1>=editable?...
};

class Map {

	std::vector<Level> Levels;
	int minLevel;
	RenderScheduler* const RS;
	SDL_Texture* MapSpriteSheet;

	public:
	Map(const std::string& MapFile, RenderScheduler* RS);
	void Reload(const std::string& MapFile);

	SDL_Texture* getMapSpriteSheet ();
	Level* getLevel (const int Level);

	void idToSprite(int id, SDL_Texture*& texture, SDL_Rect& srcrect);

	void Update(const Camera& cam);
};
