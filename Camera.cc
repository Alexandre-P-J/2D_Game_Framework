#include "Camera.h"
#include "Map.h"
#include "ExtraTypes.h"

Camera::Camera(const Position& P, int HorizontalPx, int VerticalPx, float Zoom) {
	Info.P = P;
	Info.HorizontalPx = HorizontalPx;
	Info.VerticalPx = VerticalPx;
	Info.Zoom = Zoom;
}

const Camera::Data& Camera::Get() const {
	return Info;
}

bool Camera::CanSeeObject(const Object& Obj) {
	Position ObjPos = Obj.GetPosition();
	if (std::get<2>(ObjPos) != std::get<2>(Info.P))
		return false;
	else if (std::get<0>(ObjPos) < std::get<0>(Info.P) ||
		std::get<0>(ObjPos) > std::get<0>(Info.P) + Info.HorizontalPx) {
		return false;
	}
	else if (std::get<1>(ObjPos) > std::get<1>(Info.P) ||
		std::get<1>(ObjPos) < std::get<1>(Info.P) - Info.VerticalPx) {
		return false;
	}
	return true;
}

void Camera::Update() {
	//Do Something?
}
