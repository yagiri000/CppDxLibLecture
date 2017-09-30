#include "DxLib.h"
#include "MyGlobal.h"
#include "Player.h"


const double Player::Speed = 4.0;


Player::Player() :
x(320.0),
y(240.0)
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
	DrawCircle(x, y, 24, GetColor(0, 0, 255));
}
