#pragma once
#include "Vector3D.h"

class Object {
		Vector3D position;
		bool visible = true;
	public:
		virtual void Update();
};
