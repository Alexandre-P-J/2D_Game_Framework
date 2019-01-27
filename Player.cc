#include "Player.h"
#include <iostream>
#include "Engine.h"
#include <utility>
#include "InputComponent.h"
#include <cmath>

Player::Player(b2Body* Body) {
	this->Body = Body;
	Body->SetType(b2_dynamicBody);
	//LoadPlayer();

	//P = std::make_tuple(0, 0, -1);
	//auto InputComponent = EngineUtils::getInputComponent();
	/*Bindings.push_back(InputComponent->InputBind(SDLK_w, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressW)));
	Bindings.push_back(InputComponent->InputBind(SDLK_a, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressA)));
	Bindings.push_back(InputComponent->InputBind(SDLK_s, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressS)));
	Bindings.push_back(InputComponent->InputBind(SDLK_d, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressD)));

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
//Movement();
	// Update Viewport with Player position
	auto Econf = EngineUtils::getConfiguration();
	auto MapSize = EngineUtils::getGame().lock()->getMapSize(LevelZCoordinate);
	EngineUtils::getRenderComponent()->GetViewport()->Update(getPosition(), Econf.WsizeX, Econf.WsizeY, MapSize.first, MapSize.second);



	// TESTING:
	Animations[WalkR](getPosition(), R, 5);

	return true;
}
/*
void Player::Movement() {
	int dx = 0;
	int dy = 0;
	auto movement = Speed*EngineUtils::getDelta();
	if (W_hold)
		dy -= movement;
	if (A_hold)
		dx -= movement;
	if (S_hold)
		dy += movement;
	if (D_hold)
		dx += movement;
	if (dx || dy) {
		float m = std::sqrt(dx*dx+dy*dy);
		std::get<0>(P) += dx/m;
		std::get<1>(P) += dy/m;
		double angleInRadians = std::atan2(dy, dx);
		R = (angleInRadians / M_PI) * 180.0 + 90;
	}
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
}
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
