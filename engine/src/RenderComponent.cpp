#include "RenderComponent.h"
#include <iostream>
#include <utility>
#include <cassert>


RenderComponent::RenderComponent(SDL_Renderer* Renderer, SDL_Window* Window, int maxPriorities) :
	Renderer(Renderer), Window(Window), PQueue(maxPriorities) {
		Viewport = new Camera;
	}

RenderComponent::~RenderComponent() {
	auto it = Textures.begin();
	while (it != Textures.end()) {
		SDL_DestroyTexture(it->second);
		++it;
	}
}

SDL_Texture* RenderComponent::GetTexture(const std::string& Path) {
	auto search = Textures.find(Path);
	if (search != Textures.end()) //found
		return search->second;
	else {
		SDL_Texture* texture = IMG_LoadTexture(Renderer, Path.c_str());
		Textures.insert({Path, texture});
		return texture;
	}
}

RenderComponent::RenderTask::RenderTask(SDL_Texture* texture,
  const SDL_Rect& srcrect, const SDL_Rect& dstrect, const int z, const double angle,
  const SDL_Point center, const SDL_RendererFlip flip) : texture(texture),
  srcrect(srcrect), dstrect(dstrect), z(z), angle(angle), center(center), flip(flip),
  usesRotation(true) {}

RenderComponent::RenderTask::RenderTask(SDL_Texture* texture,
  const SDL_Rect& srcrect, const SDL_Rect& dstrect, const int z) : texture(texture),
  srcrect(srcrect), dstrect(dstrect), z(z), usesRotation(false) {}

void RenderComponent::ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  const SDL_Rect srcrect, const Position Pos, const int w, const int h,
  const double angle, const SDL_Point angleCenter, const SDL_RendererFlip flip) {
	auto sPos = getPositionOnScreen(Pos);
  	SDL_Rect dstrect = {sPos.first, sPos.second, w, h};
	if (priority < 0)
		priority = 0;
	else if (priority >= PQueue.size())
		priority = PQueue.size() - 1;
	RenderTask T(texture, srcrect, dstrect, std::get<2>(Pos), angle, angleCenter, flip);
	PQueue[priority].push(T);
	++TaskNum;

}
void RenderComponent::ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  const SDL_Rect srcrect, const Position Pos, const int w, const int h) {
	auto sPos = getPositionOnScreen(Pos);
	SDL_Rect dstrect = {sPos.first, sPos.second, w, h};
	if (priority < 0)
		priority = 0;
	else if (priority >= PQueue.size())
		priority = PQueue.size() - 1;
	RenderTask T(texture, srcrect, dstrect, std::get<2>(Pos));
	PQueue[priority].push(T);
	++TaskNum;
}

void RenderComponent::ScheduleDraw(unsigned int priority, SDL_Texture* texture,
  const SDL_Rect srcrect, SDL_Rect onScreenInfo, const int z) {
	if (priority < 0)
		priority = 0;
	else if (priority >= PQueue.size())
		priority = PQueue.size() - 1;
	RenderTask T(texture, srcrect, onScreenInfo, z);
	PQueue[priority].push(T);
	++TaskNum;
}

void RenderComponent::Draw() {
	int nprior = PQueue.size();
	auto Z = std::get<2>((Viewport->Get()).P);
	for (int i = 0; i < nprior; ++i) {
		while(!PQueue[i].empty()) {
			RenderTask T = PQueue[i].front();
			if (T.z == Z) {
				if (T.usesRotation)
					SDL_RenderCopyEx(Renderer, T.texture, &(T.srcrect), &(T.dstrect),
						T.angle, &(T.center), T.flip);
				else
					SDL_RenderCopy(Renderer, T.texture, &(T.srcrect), &(T.dstrect));
			}
			PQueue[i].pop();
			--TaskNum;
		}
	}
	SDL_RenderPresent(Renderer);
	SDL_RenderClear(Renderer);
}

Camera* const RenderComponent::GetViewport() {
	return Viewport;
}

unsigned int RenderComponent::getTaskNum() {
	return TaskNum;
}

std::pair<int,int> RenderComponent::getWindowSize() {
	std::pair<int,int> WS;
	SDL_GetWindowSize(Window, &WS.first, &WS.second);
	return WS;
}
std::pair<int,int> RenderComponent::getPositionOnScreen(const Position Local) {
	auto cameraData = Viewport->Get();
	return std::make_pair(std::get<0>(Local) - std::get<0>(cameraData.P),
		std::get<1>(Local) - std::get<1>(cameraData.P));
}
