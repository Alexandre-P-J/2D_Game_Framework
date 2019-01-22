#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>
#include <utility>
#include <queue>
#include "ExtraTypes.h"

using resizeTask = std::pair<int, float>; // final size, time

class Animation {
	bool initialized = false;
	SDL_Texture* SpriteSheet;
	SDL_Rect first;
	int amount;
	int current = 0;
	std::vector<float> timing;
	float TimeSinceSpriteUpdate = 0;
	// Sprite Resize:
	std::queue<resizeTask> XresizeTasks;
	int currentXsize = first.w;
	std::queue<resizeTask> YresizeTasks;
	int currentYsize = first.h;

	SDL_Rect UpdateSprite();
	std::pair<int,int> UpdateSize();
	
public:
	Animation();
	Animation(SDL_Texture* Tex, SDL_Rect first, int amount, std::vector<float>& timing);
	void Construct(SDL_Texture* Tex, SDL_Rect first, int amount, std::vector<float>& timing);
	void operator()(Position Pos, Rotation r, int DrawPriority);

	void SetXResize(int finalXSize, float time);
	void SetYResize(int finalYSize, float time);
	void SetResize(int finalSize, float time);

	void Reset();
};
