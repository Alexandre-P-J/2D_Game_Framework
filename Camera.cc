#include "Camera.h"
#include "Map.h"
#include "ExtraTypes.h"

Camera::Camera(Position P, int width, int height) {
	Info.P = P;
	Info.VisionHeight = height;
	Info.VisionWidth = width;
}

const Camera::Data& Camera::Get() const {
	return Info;
}

bool Camera::CanSeeObject(const Object& Obj) {
	Position ObjPos = Obj.GetPosition();
	if (std::get<2>(ObjPos) != std::get<2>(Info.P))
		return false;
	else if (std::get<0>(ObjPos) < std::get<0>(Info.P) ||
		std::get<0>(ObjPos) > std::get<0>(Info.P) + Info.VisionWidth) {
		return false;
	}
	else if (std::get<1>(ObjPos) > std::get<1>(Info.P) ||
		std::get<1>(ObjPos) < std::get<1>(Info.P) - Info.VisionHeight) {
		return false;
	}
	return true;
}

void Camera::Update() {
	//Do Something?
}
