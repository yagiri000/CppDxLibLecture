#include <Siv3D.hpp>
#include "Enemy.h"
#include "GameManager.h"

const double Enemy::Radius = 24.0;

Enemy::Enemy(const Vec2 & _pos, Kind _kind) :
	pos(_pos),
	velocity(),
	kind(_kind),
	eFrame(0)
{
	if (kind == Straight) {
		velocity = RandomVec2(1.0);
	}
}

void Enemy::update() {
	if (kind == Stalker) {
		velocity = 1.5 * (gameManager.player.pos - pos).normalized();
	}
	else if (kind == Rotation) {
		velocity = Vec2(1.0, 0.0).rotate(eFrame * 0.02);
	}
	else if (kind == Straight) {

	}
	pos += velocity;
	eFrame++;
}

void Enemy::draw() {
	if (kind == Stalker) {
		Circle(pos, Radius).draw(Color(255, 0, 0));
	}
	else if (kind == Rotation) {
		Circle(pos, Radius).draw(Color(255, 128, 0));
	}
	else if (kind == Straight) {
		Circle(pos, Radius).draw(Color(255, 0, 128));
	}
}
