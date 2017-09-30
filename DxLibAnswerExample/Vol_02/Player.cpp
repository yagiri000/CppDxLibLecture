#include "Player.h"

Player::Player() :
	pos(320.0, 240.0),
	speed(5.0)
{
}

void Player::update() {
	// 上下左右キーで移動
	if (Input::KeyLeft.pressed) {
		pos.x -= speed;
	}
	if (Input::KeyRight.pressed) {
		pos.x += speed;
	}
	if (Input::KeyUp.pressed) {
		pos.y -= speed;
	}
	if (Input::KeyDown.pressed) {
		pos.y += speed;
	}
}

//自機（円）を描画
void Player::draw() {
	Circle(pos, 30.0).draw(Color(0, 0, 255));
}
