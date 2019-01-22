#pragma once
#include "RenderComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "ExtraTypes.h"
#include <chrono>
#include <vector>
#include <memory>

namespace EngineUtils {
	const float getDelta();
	RenderComponent* getRenderComponent();
	const std::shared_ptr<Game> getGame(int i = 0);
	const EngineConfig getConfiguration();
	InputComponent* getInputComponent();
}

class Engine {
	static Engine* instance;

	// ENGINE COMPONENTS:
	RenderComponent Renderer;
	InputComponent Input;
	std::vector<std::shared_ptr<Game>> GameComponents;


	// RUNTIME INFO:
	bool Running = true;
	EngineConfig config;
	float deltaTime = 1; //last frame length in ms

	int LoadEngineConfig(); //WIP

	Engine();
	Engine(SDL_Window* Window, SDL_Renderer* Renderer);

	public:
	// Singleton management
	static Engine* Construct(SDL_Window* Window, SDL_Renderer* Renderer);

	// Events:
	void ONquit();
	void ONWindowResize();

	// Run main loop
	int Run();

	// Accesible through other objects
	friend const float EngineUtils::getDelta();
	friend const EngineConfig EngineUtils::getConfiguration();
	friend const std::shared_ptr<Game> EngineUtils::getGame(int i);
	friend InputComponent* EngineUtils::getInputComponent();
	friend RenderComponent* EngineUtils::getRenderComponent();
};
