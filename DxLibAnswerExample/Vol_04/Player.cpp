#include "Player.h"

Player::Player() :
x(320.0), y(240.0),
speed(5.0)
{
}

void Player::update() {
	// ã‰º¶‰EƒL[‚ÅˆÚ“®
	if (keyState[KEY_INPUT_LEFT] > 0) {
		x -= speed;
	}
	if (keyState[KEY_INPUT_RIGHT] > 0) {
		x += speed;
	}
	if (keyState[KEY_INPUT_UP] > 0) {
		y -= speed;
	}
	if (keyState[KEY_INPUT_DOWN] > 0) {
		y += speed;
	}
}

void Player::draw() {
	DrawCircle(x, y, 30, GetColor(0, 0, 255));
}