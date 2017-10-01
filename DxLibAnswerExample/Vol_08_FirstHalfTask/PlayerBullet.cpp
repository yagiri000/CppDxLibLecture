#include <iostream>
#include "DxLib.h"
#include "PlayerBullet.h"

const double PlayerBullet::Radius = 4.0;
const double PlayerBullet::Attack = 1.0;
const unsigned int PlayerBullet::Color = 0x0000AA;
const int PlayerBullet::LifeTime = 60;

PlayerBullet::PlayerBullet(double _x, double _y, double _vx, double _vy):
	x(_x), y(_y),
	vx(_vx), vy(_vy),
	elapsedFrame(0),
	isDead(false)
{
}

void PlayerBullet::update() {
	checkDead();
	move();
	elapsedFrame++;
}

void PlayerBullet::move() {
	x += vx; y+= vy;
}

void PlayerBullet::checkDead() {
	if (elapsedFrame > LifeTime) {
		isDead = true;
	}
}

void PlayerBullet::draw() const {
	DrawCircle(x, y, Radius, Color);
}

