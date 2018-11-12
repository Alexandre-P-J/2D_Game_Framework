#pragma once
#include "RenderScheduler.h"
#include "Game.h"


class Engine { //SINGLETON
	struct Info {
		int WsizeX = 2048;
		int WsizeY = 1024;
		int FPSlimit = 144;
	};
	static Engine* instance;
	Info config;
	SDL_Window* const Window;
	SDL_Renderer* const Renderer;
	RenderScheduler* const RS;
	Game* GamePtr; //Game could be changed in runtime

	Engine();
	Engine(SDL_Window* Window, SDL_Renderer* Renderer);
public:
	~Engine();
	static Engine* getInstance();
	static Engine* Construct(SDL_Window* Window, SDL_Renderer* Renderer);
	int LoadEngineConfig();
	int Run();
	friend RenderScheduler* getRenderScheduler();
	friend const SDL_Window* getWindow();
	friend Game* getGame();
};
