#include "Enemy.h"

Enemy::Enemy(const Vec2& _pos):
	x(_x), y(_y),
	velocity(RandomVec2(5.0))
{
	// RandomVec2(double length)
	// ”¼Œalength(¡‰ñ‚Í5.0)‚Ì2ŸŒ³ƒxƒNƒgƒ‹‚ğ•Ô‚·
}

void Enemy::update() {
	x += vx; y+= vy;
}

void Enemy::draw() {
	DrawCircle(x, y, 30, GetColor(255, 0, 0));
}
