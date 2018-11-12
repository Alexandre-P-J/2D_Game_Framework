#pragma once
#include "Engine.h"
#include <cassert>

RenderScheduler* getRenderScheduler() {
	Engine* ptr = Engine::getInstance();
	assert(ptr);
	return ptr->RS;
}
const SDL_Window* getWindow() {
	Engine* ptr = Engine::getInstance();
	assert(ptr);
	return ptr->Window;
}
Game* getGame() {
	Engine* ptr = Engine::getInstance();
	assert(ptr);
	return ptr->GamePtr;
}
