#pragma once
#include "Game.h"
#include "EngineUtils.h"

Player* getPlayer(int n = 0) {
	return (getGame()->getPlayers())[n];
}
