#include "RenderScheduler.h"
#include <iostream>
#include <utility>
#include <cassert>

RenderScheduler* RenderScheduler::instance = nullptr;

RenderScheduler* RenderScheduler::getInstance() {
	return instance; // can return nullptr
}
RenderScheduler* RenderScheduler::Construct(SDL_Renderer* Renderer, SDL_Window* Window, int maxPriorities) {
	assert(!instance);
	instance = new RenderScheduler(Renderer, Window, maxPriorities);
	return instance;
}

RenderScheduler::RenderScheduler(SDL_Renderer* Renderer, SDL_Window* Window, int maxPriorities) :
	Renderer(Renderer), Window(Window), PQueue(maxPriorities) {
		Viewport = new Camera;
	}

RenderScheduler::~RenderScheduler() {
	auto it = Textures.begin();
	while (it != Textures.end()) {
		SDL_DestroyTexture(it->second);
		++it;
	}
}

SDL_Texture* RenderScheduler::GetTexture(const std::string& Path) {
	auto search = Textures.find(Path);
	if (search != Textures.end()) //found
		return search->second;
	else {
		SDL_Texture* texture = IMG_LoadTexture(Renderer, Path.c_str());
		Textures.insert({Path, texture});
		return texture;
	}
}

RenderScheduler::RenderTask::RenderTask(SDL_Texture* texture,
  const SDL_Rect& srcrect, const SDL_Rect& dstrect, const double angle,
  const SDL_Point* center, const SDL_RendererFlip flip) : texture(texture),
  srcrect(srcrect), dstrect(dstrect), angle(angle), center(center), flip(flip),
  usesRotation(true) {}

RenderScheduler::RenderTask::RenderTask(SDL_Texture* texture,
  const SDL_Rect& srcrect, const SDL_Rect& dstrect) : texture(texture),
  srcrect(srcrect), dstrect(dstrect), usesRotation(false) {}

void RenderScheduler::ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  const SDL_Rect srcrect, const Position Pos, const int w, const int h,
  const double angle, const SDL_Point* angleCenter, const SDL_RendererFlip flip) {
	auto sPos = getPositionOnScreen(Pos);
  	SDL_Rect dstrect = {sPos.first, sPos.second, w, h};
	if (priority < 0)
		priority = 0;
	else if (priority >= PQueue.size())
		priority = PQueue.size() - 1;
	RenderTask T(texture, srcrect, dstrect, angle, angleCenter, flip);
	PQueue[priority].push(T);
	++TaskNum;

}
void RenderScheduler::ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  const SDL_Rect srcrect, const Position Pos, const int w, const int h) {
	auto sPos = getPositionOnScreen(Pos);
	SDL_Rect dstrect = {sPos.first, sPos.second, w, h};
	if (priority < 0)
		priority = 0;
	else if (priority >= PQueue.size())
		priority = PQueue.size() - 1;
	RenderTask T(texture, srcrect, dstrect);
	PQueue[priority].push(T);
	++TaskNum;
}

void RenderScheduler::ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  const SDL_Rect srcrect, SDL_Rect onScreenInfo) {
	if (priority < 0)
		priority = 0;
	else if (priority >= PQueue.size())
		priority = PQueue.size() - 1;
	RenderTask T(texture, srcrect, onScreenInfo);
	PQueue[priority].push(T);
	++TaskNum;
}

void RenderScheduler::Draw() {
	int nprior = PQueue.size();
	for (int i = 0; i < nprior; ++i) {
		while(!PQueue[i].empty()) {
			RenderTask T = PQueue[i].front();
			if (T.usesRotation)
				SDL_RenderCopyEx(Renderer, T.texture, &(T.srcrect), &(T.dstrect),
					T.angle, T.center, T.flip);
			else
				SDL_RenderCopy(Renderer, T.texture, &(T.srcrect), &(T.dstrect));
			PQueue[i].pop();
			--TaskNum;
		}
	}
	SDL_RenderPresent(Renderer);
	SDL_RenderClear(Renderer);
}

Camera* const RenderScheduler::GetViewport() {
	return Viewport;
}

unsigned int RenderScheduler::getTaskNum() {
	return TaskNum;
}

std::pair<int,int> RenderScheduler::getWindowSize() {
	std::pair<int,int> WS;
	SDL_GetWindowSize(Window, &WS.first, &WS.second);
	return WS;
}
std::pair<int,int> RenderScheduler::getPositionOnScreen(const Position Local) {
	auto cameraData = Viewport->Get();
	return std::make_pair(std::get<0>(Local) - std::get<0>(cameraData.P),
		std::get<1>(Local) - std::get<1>(cameraData.P));
}
