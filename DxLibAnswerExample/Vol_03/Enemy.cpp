#include "DxLib.h"
#include "Enemy.h"

Enemy::Enemy(double _x, double _y):
	x(_x), y(_y)
{
}

void Enemy::update() {
	//下方向に移動
	y += 1.0;
}

//エネミー（円）を描画
void Enemy::draw() {
	DrawCircle(x, y, 30, GetColor(255, 0, 0));
}
