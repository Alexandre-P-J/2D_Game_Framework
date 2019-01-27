#pragma once
#include <tuple>
#include <valarray>
#include <cmath>

typedef std::tuple<float, float, int16_t> Position;
typedef std::valarray<uint32_t> IntVec;


class Rotation {
	float value = 0;
public:
	Rotation() : value(std::fmod(value, 360)) {};
	float get() const {return value;}
	Rotation operator=(float v) {value = std::fmod(v, 360); return *this;};
};

struct EngineConfig {
	int WsizeX = 2048;
	int WsizeY = 1024;
	int FPSlimit = 144;
};
