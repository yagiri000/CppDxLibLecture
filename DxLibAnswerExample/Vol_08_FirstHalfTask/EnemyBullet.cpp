#include <iostream>
#include "DxLib.h"
#include "EnemyBullet.h"

const double EnemyBullet::Radius = 8.0;
const unsigned int EnemyBullet::Color = 0xFFFFFF;
const int EnemyBullet::LifeTime = 900;

EnemyBullet::EnemyBullet(double _x, double _y, double _vx, double _vy) :
	x(_x), y(_y),
	vx(_vx), vy(_vy),
	elapsedFrame(0),
	isDead(false)
{
}

void EnemyBullet::update() {
	checkDead();
	move();
	elapsedFrame++;
}

void EnemyBullet::move() {
	x += vx; y+= vy;
}

void EnemyBullet::checkDead() {
	if (elapsedFrame > LifeTime) {
		isDead = true;
	}
}

void EnemyBullet::draw() const {
	DrawCircle(x, y, Radius, Color);
}

