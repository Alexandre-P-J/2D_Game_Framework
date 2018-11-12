#include "Engine.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <chrono>
#include <thread>

Engine* Engine::instance = nullptr;

Engine* Engine::getInstance() {
	return instance; //could return nullptr
}

Engine* Engine::Construct(SDL_Window* Window, SDL_Renderer* Renderer) {
	if (instance)
		delete instance;
	instance = new Engine(Window, Renderer);
	instance->GamePtr = new Game;
	return instance;
}

Engine::~Engine() {
	delete RS;
	delete GamePtr;
	//Both Renderer and Window are deleted at main() since arent Engine bonded
}

Engine::Engine(SDL_Window* Window, SDL_Renderer* Renderer) : Window(Window),
	Renderer(Renderer), RS(new RenderScheduler(Renderer, Window, 32)) {
		LoadEngineConfig();
		SDL_SetWindowSize(Window, config.WsizeX, config.WsizeY);
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
}

int Engine::LoadEngineConfig() {
	//WIP
	return -1; //ERR since not implemented yet.
}

int Engine::Run() {
	bool quit = false;
	while (!quit) {
		auto frame_start = std::chrono::steady_clock::now();
		GamePtr->Update();
		//MyMap.Update(cam);
		RS->Draw();
		SDL_RenderPresent(Renderer);
		SDL_RenderClear(Renderer);
		// Frame time adjustment
		std::chrono::duration<double> frame_timelength;
		do {
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			frame_timelength = (std::chrono::steady_clock::now() - frame_start)*1000;
		}
		while (frame_timelength.count() < 1000/(float)(config.FPSlimit));
	}
	return 0;
}
