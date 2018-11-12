#include "Player.h"
#include <iostream>

Player::Player(Position P, Camera& Cam) : P(P), Cam(Cam) {
	Update();
}

const Camera& Player::getCamera() {
	return Cam;
}

void Player::Update() {
	std::cout << "Player Update" << std::endl;
}
