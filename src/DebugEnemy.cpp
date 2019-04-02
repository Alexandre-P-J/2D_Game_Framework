#include "DebugEnemy.h"
#include "Engine.h"
#include <vector>
#include <iostream>

DebugEnemy::DebugEnemy(b2Body* Body) {
	this->Body = Body;
	Body->SetType(b2_dynamicBody);
	b2PolygonShape Shape;
	Shape.SetAsBox(16, 16);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Shape;
	fixtureDef.density = 10;
	fixtureDef.friction = 1;
	fixtureDef.restitution = 1;
	Body->CreateFixture(&fixtureDef);


	auto tex = EngineUtils::getRenderComponent()->GetTexture("TestDot.png");
	SDL_Rect first = {0, 0, 32, 32};
	std::vector<float> timing(1, 100);
	anim.Construct(tex, first, 1, timing);
	anim.SetResize(32, 0);
}

bool DebugEnemy::Update() {
	anim(getPosition(), getRotation(), 10);
	return true;
}
