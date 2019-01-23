#include "DebugEnemy.h"
#include "Engine.h"
#include <vector>
#include <iostream>

DebugEnemy::DebugEnemy() {
	P = std::make_tuple(0, 0, 0);
	auto tex = EngineUtils::getRenderComponent()->GetTexture("TestDot.png");
	SDL_Rect first = {0, 0, 32, 32};
	std::vector<float> timing(1, 100);
	anim.Construct(tex, first, 1, timing);
	anim.SetResize(16, 0);
}

bool DebugEnemy::Update() {
	anim(P, R, 10);
	return true;
}
