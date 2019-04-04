#pragma once
#include <tuple>
#include <valarray>
#include <cmath>

typedef std::tuple<float, float, int16_t> Position;

class Rotation {
	float value = 0;
public:
	Rotation() : value(float(std::fmod(value, 360.0f))) {};
	float get() const {return value;}
	Rotation operator=(float v) {value = float(std::fmod(v, 360.0f)); return *this;};
};
