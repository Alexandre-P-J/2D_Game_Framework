#pragma once
#include <tuple>
#include <valarray>
#include <cmath>

typedef std::tuple<uint32_t, uint32_t, int16_t> Position;
typedef std::valarray<uint32_t> IntVec;
/*Position operator+(const Position A, const Position B) {
	uint32_t X = std::get<0>(A) + std::get<0>(B);
	uint32_t Y = std::get<1>(A) + std::get<1>(B);
	uint16_t Z = std::get<2>(A) + std::get<2>(B);
	return std::make_tuple(X, Y, Z);
}*/

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
