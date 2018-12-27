#include "Player.h"
#include <iostream>
#include "Engine.h"

Player::Player() {
	//LoadPlayer();
	P = std::make_tuple(0, 0, -1);
	Bindings.push_back(Input::InputBind(SDLK_w, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressW)));
	Bindings.push_back(Input::InputBind(SDLK_a, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressA)));
	Bindings.push_back(Input::InputBind(SDLK_s, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressS)));
	Bindings.push_back(Input::InputBind(SDLK_d, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressD)));

	Bindings.push_back(Input::InputBind(SDLK_DOWN, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressArrowDown)));
}

Position Player::getPosition() const {
	return P;
}

bool Player::Update() {
	Movement();

	// Update Viewport with Player position
	auto Econf = Engine::getConfiguration();
	auto MapSize = Engine::getGame()->getMapSize(std::get<2>(P));
	Engine::getRenderScheduler()->GetViewport()->Update(P, Econf.WsizeX, Econf.WsizeY, MapSize.first, MapSize.second);

	// TESTING: Draw black square
	auto RS = Engine::getRenderScheduler();
	auto texture = RS->GetTexture("TestDot.png");
	SDL_Rect srcrect = {0, 0, 128, 128};
	auto LocalScreenPos = RS->getPositionOnScreen(P);
	SDL_Rect dstrect = {LocalScreenPos.first, LocalScreenPos.second, 16, 16};
	RS->ScheduleDraw(2, texture, srcrect, dstrect);

	return true;
}

void Player::Movement() {
	if (W_hold)
		std::get<1>(P) -= Speed*Engine::getDelta();
	if (A_hold)
		std::get<0>(P) -= Speed*Engine::getDelta();
	if (S_hold)
		std::get<1>(P) += Speed*Engine::getDelta();
	if (D_hold)
		std::get<0>(P) += Speed*Engine::getDelta();
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
	std::get<2>(P) += 1;
	std::cout << "arrow down" << std::endl;
}
