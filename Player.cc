#include "Player.h"
#include <iostream>
#include "Engine.h"
#include <utility>
#include "InputComponent.h"
#include <cmath>

Player::Player(b2Body* Body) {
	this->Body = Body;
	Body->SetType(b2_dynamicBody);
	b2PolygonShape Shape;
	Shape.SetAsBox(5, 5);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Shape;
	fixtureDef.density = 1;
	Body->CreateFixture(&fixtureDef);
	//LoadPlayer();

	auto InputComponent = EngineUtils::getInputComponent();
	Bindings.push_back(InputComponent->InputBind(SDLK_w, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressW)));
	Bindings.push_back(InputComponent->InputBind(SDLK_a, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressA)));
	Bindings.push_back(InputComponent->InputBind(SDLK_s, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressS)));
	Bindings.push_back(InputComponent->InputBind(SDLK_d, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressD)));
	/*
	Bindings.push_back(InputComponent->InputBind(SDLK_DOWN, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressArrowDown)));
	Bindings.push_back(InputComponent->InputBind(SDLK_UP, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressArrowUp)));
	*/
	auto texture = EngineUtils::getRenderComponent()->GetTexture("runner-export.png");
	SDL_Rect first = {0, 0, 128, 128};
	std::vector<float> v = {150, 100, 140, 150, 100, 140};
	Animations[WalkR].Construct(texture, first, 6, v);
	Animations[WalkR].SetResize(64, 0);
}



bool Player::Update() {
Movement();
	// Update Viewport with Player position
	auto Econf = EngineUtils::getConfiguration();
	auto MapSize = EngineUtils::getGame().lock()->getMapSize(LevelZCoordinate);
	EngineUtils::getRenderComponent()->GetViewport()->Update(getPosition(), Econf.WsizeX, Econf.WsizeY, MapSize.first, MapSize.second);



	// TESTING:
	Animations[WalkR](getPosition(), R, 5);

	return true;
}

void Player::Movement() {
	b2Vec2 Speed = {0, 0};
	auto movement = WalkSpeed*EngineUtils::getDelta();
	if (W_hold)
		Speed.y -= movement;
	if (A_hold)
		Speed.x -= movement;
	if (S_hold)
		Speed.y += movement;
	if (D_hold)
		Speed.x += movement;
	if (Speed.x || Speed.y) {
		double angleInRadians = std::atan2(Speed.y, Speed.x);
		R = (angleInRadians / M_PI) * 180.0 + 90;
	}
	Body->SetLinearVelocity(Speed);
}

void Player::ON_KeyPressW(Uint8 state) {
	W_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressA(Uint8 state) {
	A_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressS(Uint8 state) {
	S_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressD(Uint8 state) {
	D_hold = (state == SDL_PRESSED);
}/*
void Player::ON_KeyPressArrowDown(Uint8 state) {
	auto LevelIDinterval = EngineUtils::getGame().lock()->getMapLevelsInterval();
	if (std::get<2>(P) > LevelIDinterval.first)
		std::get<2>(P) -= 1;
}
void Player::ON_KeyPressArrowUp(Uint8 state) {
	auto LevelIDinterval = EngineUtils::getGame().lock()->getMapLevelsInterval();
	if (std::get<2>(P) < LevelIDinterval.second)
		std::get<2>(P) += 1;
}
*/
