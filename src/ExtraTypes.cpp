#include "ExtraTypes.h"
#include <tuple>
#include <cmath>

Position operator+(const Position A, const Position B) {
	float X = std::get<0>(A) + std::get<0>(B);
	float Y = std::get<1>(A) + std::get<1>(B);
	uint16_t Z = std::get<2>(A) + std::get<2>(B);
	return std::make_tuple(X, Y, Z);
}
