#include "Enemy.h"

Enemy::Enemy(double _x, double _y):
	x(_x), y(_y),
	vx((double)(GetRand(5) - 2)), 
	vy((double)(GetRand(5) - 2)) // “K“–‚È‘¬“x‚ğİ’è
{
}

void Enemy::update() {
	x += vx; y+= vy;
}

void Enemy::draw() {
	DrawCircle(x, y, 30, GetColor(255, 0, 0));
}
