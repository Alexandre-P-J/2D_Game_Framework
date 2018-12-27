#include "Input.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <cassert>

Input* Input::instance = nullptr;

Input* Input::getInstance() {
	return instance; //could return nullptr
}

Input* Input::Construct() {
	if (instance)
		delete instance;
	instance = new Input();
	return instance;
}



uint64_t Input::InputBind(std::uint32_t Type, fastdelegate::FastDelegate0<> Delegate) {
	auto Ptr = Input::getInstance();
	assert(Ptr);
	auto stat = Ptr->GlobalIN.insert(std::make_pair(Type, Event<>()));
	uint32_t id;
	if (!stat.second)
		id = (Ptr->GlobalIN[Type]).Bind(Delegate);
	else
		id = (stat.first)->second.Bind(Delegate);
	Ptr->GlobalIN_IDS.insert(std::make_pair(id, stat.first));
	return merge(id, 0);
}

uint64_t Input::InputBind(SDL_Keycode Key, fastdelegate::FastDelegate1<Uint8> Delegate) {
	auto Ptr = Input::getInstance();
	assert(Ptr);
	auto stat = Ptr->KeyIN.insert(std::make_pair(Key, Event<Uint8>()));
	uint32_t id;
	if (!stat.second)
		id = (Ptr->KeyIN[Key]).Bind(Delegate);
	else
		id = (stat.first)->second.Bind(Delegate);
	Ptr->KeyIN_IDS.insert(std::make_pair(id, stat.first));
	return merge(id, 1);
}

uint64_t Input::InputBind(std::uint32_t Type, Uint8 WindowAction, fastdelegate::FastDelegate0<> Delegate) {
	auto Ptr = Input::getInstance();
	assert(Ptr);
	auto stat = Ptr->WindowIN.insert(std::make_pair(std::make_pair(Type,WindowAction), Event<>()));
	uint32_t id;
	if (!stat.second)
		id = (Ptr->WindowIN[std::make_pair(Type,WindowAction)]).Bind(Delegate);
	else
		id = (stat.first)->second.Bind(Delegate);
	Ptr->WindowIN_IDS.insert(std::make_pair(id, stat.first));
	return merge(id, 2);
}


void Input::InputUnbind(const uint64_t uniqueID) {
	auto type = splitsecond(uniqueID);
	auto id = splitfirst(uniqueID);
	auto Ptr = Input::getInstance();
	assert(Ptr);
	switch (type) {
		case 0: {
			auto it = Ptr->GlobalIN_IDS.find(id);
			if (it != Ptr->GlobalIN_IDS.end()) {
				((it->second)->second).UnBind(id);
				if (((it->second)->second).size() == 0)
					Ptr->GlobalIN.erase(it->second);
				Ptr->GlobalIN_IDS.erase(it);
			}
			break;
		}
		case 1: {
			auto it = Ptr->KeyIN_IDS.find(id);
			if (it != Ptr->KeyIN_IDS.end()) {
				((it->second)->second).UnBind(id);
				if (((it->second)->second).size() == 0)
					Ptr->KeyIN.erase(it->second);
				Ptr->KeyIN_IDS.erase(it);
			}
			break;
		}
		case 2: {
			auto it = Ptr->WindowIN_IDS.find(id);
			if (it != Ptr->WindowIN_IDS.end()) {
				((it->second)->second).UnBind(id);
				if (((it->second)->second).size() == 0)
					Ptr->WindowIN.erase(it->second);
				Ptr->WindowIN_IDS.erase(it);
			}
			break;
		}
	}
}



void Input::Run() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			//SPECIAL EVENTS
			case SDL_QUIT: {
				auto it = GlobalIN.find(event.type);
				if (it != GlobalIN.end())
					(it->second)();
				break;
			}

			// WINDOW INTERACTIONS
			case SDL_WINDOWEVENT: {
				Uint8 WindowAction = (event.window).event;
				auto it = WindowIN.find(std::make_pair(event.type, WindowAction));
				if (it != WindowIN.end())
					(it->second)();
				break;
			}
			/*
			case SDL_MOUSEBUTTONDOWN:
				switch ((event.button).button) {
					case SDL_BUTTON_LEFT:
						break;
					case SDL_BUTTON_RIGHT:
						break;
				}
				break;
			*/

			// KEYBOARD KEYS
			case SDL_KEYDOWN: {
				SDL_Keycode KeyCode = ((event.key).keysym).sym;
				auto it = KeyIN.find(KeyCode);
				if (it != KeyIN.end())
					(it->second)((event.key).state);
				break;
			}
			case SDL_KEYUP: {
				SDL_Keycode KeyCode = ((event.key).keysym).sym;
				auto it = KeyIN.find(KeyCode);
				if (it != KeyIN.end())
					(it->second)((event.key).state);
				break;
			}
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
