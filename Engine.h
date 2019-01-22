#pragma once
#include "RenderScheduler.h"
#include "Game.h"
#include "Input.h"
#include "ExtraTypes.h"
#include <chrono>
#include <vector>
#include <memory>

class Engine {
	static Engine* instance;

	// ENGINE COMPONENTS:
	const std::shared_ptr<RenderScheduler> RenderComponent;
	std::vector<std::shared_ptr<Game>> GameComponents;
	const std::unique_ptr<Input> InputComponent;

	// RUNTIME INFO:
	bool Running = true;
	EngineConfig config;
	float deltaTime = 0; //last frame length

	int LoadEngineConfig(); //WIP

	Engine();
	Engine(SDL_Window* Window, SDL_Renderer* Renderer);

	public:

	// Singleton management
	static inline Engine* getInstance();
	static Engine* Construct(SDL_Window* Window, SDL_Renderer* Renderer);

	// Events:
	void ONquit();
	void ONWindowResize();

	// Run main loop
	int Run();

	// Accesible through other objects
	static const float getDelta();
	static std::shared_ptr<RenderScheduler> getRenderScheduler();
	static const std::shared_ptr<Game> getGame(int i = 0);
	static const EngineConfig getConfiguration();
};
