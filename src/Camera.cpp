#include "Camera.h"
#include "Map.h"
#include "ExtraTypes.h"
#include <iostream>

Camera::Camera() {
	Info.P = Position(0, 0, -1);
	Info.HorizontalPx = 0;
	Info.VerticalPx = 0;
	Info.Zoom = 1;
}

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
	Position ObjPos = Obj.getPosition();
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


void Camera::Update(const Position PlayerPos, int HorizontalPx, int VerticalPx, uint32_t MapWidthpx, uint32_t MapHeightpx) {
	Info.HorizontalPx = HorizontalPx;
	Info.VerticalPx = VerticalPx;
	int y = std::get<1>(PlayerPos) - (VerticalPx/2);
	if (y < 0)
		y = 0;
	if (y+VerticalPx >= MapHeightpx-64)
		y = MapHeightpx-VerticalPx-64;
	int x = std::get<0>(PlayerPos) - (HorizontalPx/2);
	if (x < 0)
		x = 0;
	if (x+HorizontalPx >= MapWidthpx-32)
		x = MapWidthpx-HorizontalPx-32;
	Info.P = std::make_tuple(x, y, std::get<2>(PlayerPos));
}
