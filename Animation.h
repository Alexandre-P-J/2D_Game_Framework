#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <vector>

class Animation {
	SDL_Texture* SpriteSheet;
	SDL_Rect first;
	int amount;
	int current = 0;
	float SpeedMultiplier = 1;
	std::vector<float> timing;
	float TimeSinceUpdate = 0;
	void Draw(int x, int y, int DrawPriority);
public:
	Animation(SDL_Texture* Tex, SDL_Rect first, int amount, std::vector<float>& timing);
	void operator()(int x, int y, int DrawPriority);
};
