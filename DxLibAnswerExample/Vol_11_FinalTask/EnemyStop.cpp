#include <memory>
#include "MyGlobal.h"
#include "GameManager.h"
#include "EnemyStop.h"
#include "EnemyBullet.h"


const size_t EnemyStop::EnemyshotRate = 60;
const double EnemyStop::BulletSpeed = 1.0;
const double EnemyStop::Radius = 24.0;
const double EnemyStop::Hp = 5.0;
const int EnemyStop::Score = 100;
const unsigned int EnemyStop::Color = 0xFF8800;

EnemyStop::EnemyStop(double _x, double _y) :
	IEnemy(_x, _y, 0.0, 0.0, Radius, Hp, Score, Color)
{
}

void EnemyStop::move() {
	vx = 0.0;
	vy = 0.0;
	x += vx;
	y += vy;
}

void EnemyStop::shot() {
	// プレイヤーに向けてショットを撃つ
	if (elapsedFrame % EnemyshotRate == 0) {
		double bx, by;
		Player& p = gameManager.player;
		normalize(x, y, p.x, p.y, &bx, &by);
		bx *= BulletSpeed;
		by *= BulletSpeed;
		gameManager.enemyBulletManager.add(std::make_shared<EnemyBullet>(x, y, bx, by));
	}
}
