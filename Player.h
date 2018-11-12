#pragma once
#include "Object.h"
#include "Camera.h"

class Player : public Object {
		Position P;
		Camera Cam;
	public:
		Player(Position P, Camera& Cam);
		const Camera& getCamera();
		void Update();
};
