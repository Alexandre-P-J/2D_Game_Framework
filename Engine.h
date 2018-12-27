#pragma once
#include "RenderScheduler.h"
#include "Game.h"
#include "Input.h"
#include "ExtraTypes.h"
#include <chrono>

class Engine {
	static Engine* instance;
	// ENGINE COMPONENTS:
	RenderScheduler* const RenderComponent;
	Game* GameComponent;
	Input* const InputComponent;

	// RUNTIME INFO:
	bool Running = true;
	EngineConfig config;
	float deltaTime = 0; //last frame length

	int LoadEngineConfig(); //WIP
public:
	Engine();
	Engine(SDL_Window* Window, SDL_Renderer* Renderer);
	~Engine();
	void ONquit();
	void ONWindowResize();

	static inline Engine* getInstance();
	static Engine* Construct(SDL_Window* Window, SDL_Renderer* Renderer);

	int Run();

	static const float getDelta();
	static RenderScheduler* getRenderScheduler();
	static Game* getGame();
	static const EngineConfig getConfiguration();
};
