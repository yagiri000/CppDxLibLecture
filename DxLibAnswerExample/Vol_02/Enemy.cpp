# include <Siv3D.hpp>
# include "Enemy.h"

Enemy::Enemy(Vec2 _pos):
	pos(_pos)
{
}

void Enemy::update() {
	//下方向に移動
	pos.y += 1.0;
}

//エネミー（円）を描画
void Enemy::draw() {
	Circle(pos, 30.0).draw(Color(255, 0, 0));
}
