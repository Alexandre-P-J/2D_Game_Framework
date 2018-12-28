#include "Animation.h"
#include "Engine.h"
#include <cassert>

Animation::Animation(SDL_Texture* Tex, SDL_Rect first, int amount,
	std::vector<float>& timing) : SpriteSheet(Tex), first(first), amount(amount),
	timing(timing) {
		assert(timing.size() == amount);
	}

void Animation::Draw(int x, int y, int DrawPriority) {
	int Th, Tw;
	SDL_QueryTexture(SpriteSheet, NULL, NULL, &Tw, &Th);

	auto rect = first;
	rect.x = ((current*first.w)+first.x) % Tw;
	rect.y = (current/(Tw/first.w))*first.h;
	SDL_Rect dstrect = {x, y, first.w, first.h};
	Engine::getRenderScheduler()->ScheduleDraw(DrawPriority, SpriteSheet, rect, dstrect);
}

void Animation::operator()(int x, int y, int DrawPriority) {
	auto Delta = Engine::getDelta();
	TimeSinceUpdate += Delta;
	if (timing[current] <= TimeSinceUpdate) {
		Draw(x, y, DrawPriority);
		current = (current + 1) % amount;
		TimeSinceUpdate = 0;
	}
	else if (timing[current] - TimeSinceUpdate < std::abs(timing[current] - (TimeSinceUpdate + Delta))) {
		Draw(x, y, DrawPriority);
		current = (current + 1) % amount;
		TimeSinceUpdate = 0;
	}
	else
		Draw(x, y, DrawPriority);
}
