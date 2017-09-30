#include <Siv3D.hpp>
#include "Player.h"


const double Player::Speed = 4.0;


Player::Player() :
pos(Vec2(320.0, 240.0))
{
}

void Player::update() {
	// è„â∫ç∂âEÉLÅ[Ç≈à⁄ìÆ
	if (Input::KeyLeft.pressed) {
		pos.x -= Speed;
	}
	if (Input::KeyRight.pressed) {
		pos.x += Speed;
	}
	if (Input::KeyUp.pressed) {
		pos.y -= Speed;
	}
	if (Input::KeyDown.pressed) {
		pos.y += Speed;
	}
}

void Player::draw() {
	Circle(pos, 24.0).draw(Color(0, 0, 255));
}
