#include "Animation.h"
#include "Engine.h"
#include <cassert>
#include <iostream>

Animation::Animation() {};

Animation::Animation(SDL_Texture* Tex, SDL_Rect first, int amount,
	std::vector<float>& timing) : SpriteSheet(Tex), first(first), amount(amount),
	timing(timing) {
		assert(timing.size() == amount);
		initialized = true;
}

void Animation::Construct(SDL_Texture* Tex, SDL_Rect first, int amount,
	std::vector<float>& timing) {
		SpriteSheet = Tex;
		this->first = first;
		this->amount = amount;
		this->timing = timing;
		assert(timing.size() == amount);
		initialized = true;
}

SDL_Rect Animation::UpdateSprite() {
	int Th, Tw;
	SDL_QueryTexture(SpriteSheet, NULL, NULL, &Tw, &Th);
	SDL_Rect rect = {((current*first.w)+first.x) % Tw, (current/(Tw/first.w))*first.h + first.y, first.w, first.h};
	//Update time:
	auto Delta = Engine::getDelta();
	TimeSinceSpriteUpdate += Delta;
	if (timing[current] <= TimeSinceSpriteUpdate) {
		TimeSinceSpriteUpdate = TimeSinceSpriteUpdate - timing[current];
		current = (current + 1) % amount;
	}
	else if (timing[current] - TimeSinceSpriteUpdate < std::abs(timing[current] - (TimeSinceSpriteUpdate + Delta))) {
		TimeSinceSpriteUpdate = (timing[current] - TimeSinceSpriteUpdate) * -1;
		current = (current + 1) % amount;
	}
	return rect;
}

std::pair<int,int> Animation::UpdateSize() {
	auto Delta = Engine::getDelta();
	if (!XresizeTasks.empty()) {
		auto task = XresizeTasks.front();
		auto finalXsize = task.first;
		auto XresizeTime = task.second;
		if (finalXsize != currentXsize) {
			if (XresizeTime > Delta) {
				int dx = std::round((finalXsize - currentXsize) / (XresizeTime/Delta));
				currentXsize += dx;
				XresizeTime -= Delta;
			}
			else {
				currentXsize = finalXsize;
				XresizeTime = 0;
			}
			if (finalXsize == currentXsize)
				XresizeTasks.pop();
			else
				(XresizeTasks.front()).second = XresizeTime;
		}
	}
	if (!YresizeTasks.empty()) {
		auto task = YresizeTasks.front();
		auto finalYsize = task.first;
		auto YresizeTime = task.second;
		if (finalYsize != currentYsize) {
			if (YresizeTime > Delta) {
				int dy = std::round((finalYsize - currentYsize) / (YresizeTime/Delta));
				currentYsize += dy;
				YresizeTime -= Delta;
			}
			else {
				currentYsize = finalYsize;
				YresizeTime = 0;
			}
			if (finalYsize == currentYsize)
				YresizeTasks.pop();
			else
				(YresizeTasks.front()).second = YresizeTime;
		}
	}
	return std::make_pair(currentXsize, currentYsize);
}

void Animation::operator()(Position Pos, Rotation r, int DrawPriority) {
	if (initialized) {
		auto srcrect = UpdateSprite();
		auto WH = UpdateSize();
		//Engine::getRenderScheduler()->ScheduleDraw(DrawPriority, SpriteSheet, srcrect, Pos, WH.first, WH.second);
		SDL_Point center = {WH.first/2, WH.second/2};
		Engine::getRenderScheduler()->ScheduleDraw(DrawPriority, SpriteSheet, srcrect, Pos, WH.first, WH.second, r.ToDouble(), center, SDL_FLIP_NONE);
	}
}

void Animation::SetXResize(int finalXSize, float time) {
	XresizeTasks.push(std::make_pair(finalXSize, time));
}
void Animation::SetYResize(int finalYSize, float time) {
	YresizeTasks.push(std::make_pair(finalYSize, time));
}
void Animation::SetResize(int finalSize, float time) {
	XresizeTasks.push(std::make_pair(finalSize, time));
	YresizeTasks.push(std::make_pair(finalSize, time));
}

void Animation::Reset() {
	XresizeTasks = std::queue<resizeTask>();
	YresizeTasks = std::queue<resizeTask>();
	current = 0;
	TimeSinceSpriteUpdate = 0;
	currentXsize = first.w;
	currentYsize = first.h;
}
