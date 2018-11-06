#pragma once
#include "ExtraTypes.h"
#include "Object.h"

class Camera {
		struct Data {
			Position P;
			int VisionHeight;
			int VisionWidth;
		};
		Data Info;
	public:
		Camera(Position P, int VisionWidth, int VisionHeight);
		const Data& Get() const;
		bool CanSeeObject(const Object& Obj);
		void Update();
};
