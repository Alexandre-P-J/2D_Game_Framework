#pragma once
#include "ExtraTypes.h"
#include "Object.h"

class Camera {
		struct Data {
			Position P;
			unsigned int HorizontalPx;
			unsigned int VerticalPx;
			float Zoom = 1;
		};
		Data Info;
	public:
		Camera(const Position& P, int HorizontalPx, int VerticalPx, float Zoom);
		const Data& Get() const;
		bool CanSeeObject(const Object& Obj);
		void Update();
};
