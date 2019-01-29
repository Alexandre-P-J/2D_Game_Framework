#include "Engine.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cassert>

Engine* Engine::instance = nullptr;

Engine* Engine::Construct(SDL_Window* Window, SDL_Renderer* Renderer) {
	if (instance)
		delete instance;
	instance = new Engine(Window, Renderer);
	instance->GameComponent = std::make_shared<Game>();
	return instance;
}


Engine::Engine(SDL_Window* Window, SDL_Renderer* Renderer) : Renderer(Renderer, Window, 32) {
		LoadEngineConfig();
		SDL_SetWindowSize(Window, config.WsizeX, config.WsizeY);
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
		Input.InputBind(SDL_QUIT, fastdelegate::MakeDelegate(this, &Engine::ONquit));
		Input.InputBind(SDL_WINDOWEVENT, SDL_WINDOWEVENT_RESIZED, fastdelegate::MakeDelegate(this, &Engine::ONWindowResize));
}

int Engine::LoadEngineConfig() {
	//WIP
	return -1; //ERR since not implemented yet.
}

void Engine::ONquit() {
	Running = false; //the Run loop will break
}

void Engine::ONWindowResize() {
	auto Wsize = Renderer.getWindowSize();
	config.WsizeX = Wsize.first;
	config.WsizeY = Wsize.second;
	std::cout << "Resizee" << std::endl;
}


int Engine::Run() {
	GameComponent->MapSnapshotToWorkingMap();
	do {
		//FRAME TIME START
		auto frame_start = std::chrono::steady_clock::now();
		//GAME UPDATE
		GameComponent->Update();
		//PHYSICS UPDATE
		auto Worlds = GameComponent->getPhysicsToUpdate();
		for (auto World : Worlds) {
			float TimeAcumulator = *(World.second) + deltaTime/1000;
			while (TimeAcumulator >= config.PhysicsTimeStep) {
				(World.first)->Step(config.PhysicsTimeStep, config.PhysicsVelocityIterations, config.PhysicsPositionIterations);
				TimeAcumulator -= config.PhysicsTimeStep;
			}
			*(World.second) = TimeAcumulator;
		}
		//DRAW
		Renderer.Draw();
		// INPUT
		Input.Run();
		// FRAME TIME END, DO ADJUSTMENT IF NEEDED
		std::chrono::duration<double> frame_timelength;
		do {
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			frame_timelength = (std::chrono::steady_clock::now() - frame_start)*1000;
		}
		while (frame_timelength.count() < 1000/(float)(config.FPSlimit));
		deltaTime = frame_timelength.count();
	}
	while (Running);
	return 0;
}

const float EngineUtils::getDelta() {
	Engine* ptr = Engine::instance;
	assert(ptr);
	return ptr->deltaTime;
}
RenderComponent* EngineUtils::getRenderComponent() {
	Engine* ptr = Engine::instance;
	assert(ptr);
	return &(ptr->Renderer);
}
std::weak_ptr<Game> EngineUtils::getGame() {
	Engine* ptr = Engine::instance;
	assert(ptr);
	return std::weak_ptr<Game>(ptr->GameComponent);
}
const EngineConfig EngineUtils::getConfiguration() {
	Engine* ptr = Engine::instance;
	assert(ptr);
	return ptr->config;
}
InputComponent* EngineUtils::getInputComponent() {
	Engine* ptr = Engine::instance;
	assert(ptr);
	return &(ptr->Input);
}
