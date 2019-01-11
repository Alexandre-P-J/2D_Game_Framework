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
	Bindings.push_back(Input::InputBind(SDLK_UP, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressArrowUp)));

	auto texture = Engine::getRenderScheduler()->GetTexture("runner-export.png");
	SDL_Rect first = {0, 0, 128, 128};
	std::vector<float> v = {150, 100, 140, 150, 100, 140};
	Animations[WalkR].Construct(texture, first, 6, v);
	Animations[WalkR].SetResize(64, 0);

}



bool Player::Update() {
	Movement();

	// Update Viewport with Player position
	auto Econf = Engine::getConfiguration();
	auto MapSize = Engine::getGame()->getMapSize(std::get<2>(P));
	Engine::getRenderScheduler()->GetViewport()->Update(P, Econf.WsizeX, Econf.WsizeY, MapSize.first, MapSize.second);



	// TESTING:
	Animations[WalkR](P, 5);

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
	auto LevelIDinterval = Engine::getGame()->getMapLevelsInterval();
	if (std::get<2>(P) > LevelIDinterval.first)
		std::get<2>(P) -= 1;
}
void Player::ON_KeyPressArrowUp(Uint8 state) {
	auto LevelIDinterval = Engine::getGame()->getMapLevelsInterval();
	if (std::get<2>(P) < LevelIDinterval.second)
		std::get<2>(P) += 1;
}
