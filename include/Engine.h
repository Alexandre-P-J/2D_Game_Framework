#pragma once
#include "RenderComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "ExtraTypes.h"
#include <chrono>
#include <vector>
#include <memory>

struct EngineConfig {
	int WsizeX = 2048;
	int WsizeY = 1024;
	int FPSlimit = 144;
	const float PhysicsTimeStep = 1/300.f;
	const int PhysicsVelocityIterations = 8;
	const int PhysicsPositionIterations = 2;
};

namespace EngineUtils {
	const float getDelta();
	RenderComponent* getRenderComponent();
	std::weak_ptr<Game> getGame();
	const EngineConfig getConfiguration();
	InputComponent* getInputComponent();
}

class Engine {
	static Engine* instance;

	// ENGINE COMPONENTS:
	RenderComponent Renderer;
	InputComponent Input;
	std::shared_ptr<Game> GameComponent;

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
	friend std::weak_ptr<Game> EngineUtils::getGame();
	friend InputComponent* EngineUtils::getInputComponent();
	friend RenderComponent* EngineUtils::getRenderComponent();
};
