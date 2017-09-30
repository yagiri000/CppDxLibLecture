# include "Enemy.h"

Enemy::Enemy(const Vec2& _pos):
	pos(_pos),
	velocity(RandomVec2(5.0))
{
	// RandomVec2(double length)
	// ”¼Œalength(¡‰ñ‚Í5.0)‚Ì2ŸŒ³ƒxƒNƒgƒ‹‚ğ•Ô‚·
}

void Enemy::update() {
	pos += velocity;
}

void Enemy::draw() {
	Circle(pos, 30.0).draw(Color(255, 0, 0));
}
