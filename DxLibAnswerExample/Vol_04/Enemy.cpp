# include "Enemy.h"

Enemy::Enemy(const Vec2& _pos):
	pos(_pos),
	velocity(0.0, 0.0)
{
}

void Enemy::update() {
	// プレイヤーから敵のベクトルを引き、正規化したものにSpeedを掛けて常に一定の速度で動くようにする
	// （ベクトルがよくわからない方へ：プレイヤー方向への速度を出してるだけです）
	const double Speed = 1.5;
	velocity = playerPtr->pos - pos;
	velocity = Speed * velocity.normalized();
	pos += velocity;
}

void Enemy::draw() {
	Circle(pos, 30.0).draw(Color(255, 0, 0));
}

// プレイヤーへのポインタを取得する関数
void Enemy::setPlayerPtr(Player * ptr_){
	playerPtr = ptr_;
}
