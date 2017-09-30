#include "DxLib.h"
#include "Player.h"


const double Player::Speed = 4.0;


Player::Player() :
pos(Vec2(320.0, 240.0))
{
}

void Player::update() {
	// ã‰º¶‰EƒL[‚ÅˆÚ“®
	if (keyState[KEY_INPUT_LEFT] > 0) {
		x -= Speed;
	}
	if (keyState[KEY_INPUT_RIGHT] > 0) {
		x += Speed;
	}
	if (keyState[KEY_INPUT_UP] > 0) {
		y -= Speed;
	}
	if (keyState[KEY_INPUT_DOWN] > 0) {
		y += Speed;
	}
}

void Player::draw() {
	Circle(pos, 24.0).draw(Color(0, 0, 255));
}
