#pragma once
#include <tuple>

typedef std::tuple<uint32_t, uint32_t, int16_t> Position;

struct EngineConfig {
	int WsizeX = 2048;
	int WsizeY = 1024;
	int FPSlimit = 144;
};
