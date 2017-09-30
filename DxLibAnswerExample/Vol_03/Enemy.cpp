# include "Enemy.h"

Enemy::Enemy(Vec2 _pos):
	pos(_pos),
	velocity(0.0, 1.0)
{
}

void Enemy::update() {
	pos += velocity;
}

//エネミー（円）を描画
void Enemy::draw() {
	Circle(pos, 30.0).draw(Color(255, 0, 0));
}
