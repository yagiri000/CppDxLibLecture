#include "Enemy.h"
#include "MyGlobal.h"

Enemy::Enemy(double _x, double _y):
	x(_x), y(_y),
	vx(0.0), vy(0.0)
{
}

void Enemy::update() {
	// プレイヤーから敵のベクトルを引き、正規化したものにSpeedを掛けて常に一定の速度で動くようにする
	// プレイヤー方向に一定速度で移動
	const double Speed = 1.5;
	normalize(x, y, playerPtr->x, playerPtr->y, &vx, &vy);
	vx *= Speed;
	vy *= Speed;
	x += vx;
	y+= vy;
}

void Enemy::draw() {
	DrawCircle(x, y, 30, GetColor(255, 0, 0));
}

// プレイヤーへのポインタを取得する関数
void Enemy::setPlayerPtr(Player * ptr_){
	playerPtr = ptr_;
}
