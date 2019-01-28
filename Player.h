#pragma once
#include "Object.h"
#include "Camera.h"
#include <vector>
#include "Animation.h"

class Player : public Object {
		// General:
		float WalkSpeed = 15;
		// Animations:
		enum AnimationType {WalkF = 0, WalkR, WalkB, WalkL, IdleF, IdleR, IdleB,
			IdleL, ANIMATION_COUNT};
		struct AnimArray {
			Animation Animations[ANIMATION_COUNT];
			inline Animation& operator[](AnimationType Anim) {
				return Animations[Anim];
			}
		};
		AnimArray Animations;
		// Input Handling:
		std::vector<uint64_t> Bindings;
		bool W_hold = false;
		bool A_hold = false;
		bool S_hold = false;
		bool D_hold = false;
		// Load
		void LoadPlayer(); //WIP
	public:
		Player(b2Body* Body);
		// General
		bool Update();

		void Movement();
		// Events
		void ON_KeyPressW(Uint8 state);
		void ON_KeyPressA(Uint8 state);
		void ON_KeyPressS(Uint8 state);
		void ON_KeyPressD(Uint8 state);
		void ON_KeyPressE(Uint8 state);
		/*void ON_KeyPressArrowDown(Uint8 state);
		void ON_KeyPressArrowUp(Uint8 state);*/
};

REGISTER_TYPE(Player)
