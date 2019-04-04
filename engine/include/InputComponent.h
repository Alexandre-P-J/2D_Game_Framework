#pragma once
#include "Event.h"
#include "SDL2/SDL.h"
#include <cstdint>
#include <map>
#include <utility>

class InputComponent {
		std::map<std::uint32_t, Event<>> GlobalIN;
		std::map<uint32_t, std::map<std::uint32_t, Event<>>::iterator> GlobalIN_IDS;

		std::map<SDL_Keycode, Event<Uint8>> KeyIN;
		std::map<uint32_t, std::map<SDL_Keycode, Event<Uint8>>::iterator> KeyIN_IDS;

		std::map<std::pair<std::uint32_t,Uint8>, Event<>> WindowIN;
		std::map<uint32_t, std::map<std::pair<std::uint32_t,Uint8>, Event<>>::iterator> WindowIN_IDS;

	public:
		uint64_t InputBind(std::uint32_t Type, fastdelegate::FastDelegate0<> Delegate);
		uint64_t InputBind(SDL_Keycode Key, fastdelegate::FastDelegate1<Uint8> Delegate);
		uint64_t InputBind(std::uint32_t Type, Uint8 WindowAction, fastdelegate::FastDelegate0<> Delegate);

		void InputUnbind(const uint64_t uniqueID);

		void Run();
};

inline uint64_t const merge(uint32_t first, uint32_t second) {
	uint64_t number = (uint64_t(first) << 32) | second;
	return number;
}
inline uint32_t const splitfirst(uint64_t number) {
	return uint32_t(number >> 32);
}
inline uint32_t const splitsecond(uint64_t number) {
	return uint32_t(number);
}
