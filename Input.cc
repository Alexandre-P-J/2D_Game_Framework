#include "Input.h"

void Input::Run() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				switch ((event.button).button) {
					case SDL_BUTTON_LEFT:
						break;
					case SDL_BUTTON_RIGHT:
						break;
				}
				break;

			case SDL_KEYDOWN:
				switch (((event.key).keysym).sym) {
					case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				}
				break;
		}
	}
}
/*
SDL_KeyboardEvent
SDL_MouseMotionEvent
SDL_MouseButtonEvent
SDL_MouseWheelEvent

SDL_JoyAxisEvent
SDL_JoyBallEvent
SDL_JoyHatEvent
SDL_JoyButtonEvent
SDL_JoyDeviceEvent

SDL_ControllerAxisEvent
SDL_ControllerButtonEvent
SDL_ControllerDeviceEvent

SDL_QuitEvent

SDL_DropEvent
*/
