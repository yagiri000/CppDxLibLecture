#include "Player.h"
#include "MyGlobal.h"

Player::Player() :
	x(320.0), y(240.0),
	speed(5.0)
{
}

void Player::update() {
	// 上下左右キーで移動
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

//自機（円）を描画
void Player::draw() {
	DrawCircle(x, y, 30, GetColor(0, 0, 255));
}
