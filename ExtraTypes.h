#pragma once
#include <tuple>
#include <valarray>
#include <cmath>

typedef std::tuple<double, double, int16_t> Position;
typedef std::valarray<uint32_t> IntVec;


class Rotation {
	double value = 0;
public:
	Rotation() : value(std::fmod(value, 360)) {};
	double ToDouble() const {return value;}
	Rotation operator=(double v) {value = std::fmod(v, 360); return *this;};
};

struct EngineConfig {
	int WsizeX = 2048;
	int WsizeY = 1024;
	int FPSlimit = 144;
};
