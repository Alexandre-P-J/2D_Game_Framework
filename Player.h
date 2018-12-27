#pragma once
#include "Object.h"
#include "Camera.h"
#include <vector>

class Player : public Object {
		Position P;
		float Speed = 0.35;
		std::vector<uint64_t> Bindings;
		bool W_hold = false;
		bool A_hold = false;
		bool S_hold = false;
		bool D_hold = false;
		void LoadPlayer(); //WIP
	public:
		Player();
		Position getPosition() const;

		bool Update();
		void Movement();

		void ON_KeyPressW(Uint8 state);
		void ON_KeyPressA(Uint8 state);
		void ON_KeyPressS(Uint8 state);
		void ON_KeyPressD(Uint8 state);
		void ON_KeyPressArrowDown(Uint8 state);
};
