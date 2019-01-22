#include "SDL2/SDL.h"
#include "Engine.h"


int main() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_RESIZABLE, &Window, &Renderer);

	auto Engine = Engine::Construct(Window, Renderer);
	Engine->Run();

	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
