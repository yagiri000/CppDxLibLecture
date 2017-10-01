#include <memory>
#include "MyGlobal.h"
#include "GameManager.h"
#include "EnemyBullet.h"
#include "EnemyRotation.h"

const size_t EnemyRotation::EnemyshotRate = 120;
const size_t EnemyRotation::EnemyshotNum = 4;
const double EnemyRotation::EnemyBulletSpeed = 8.0;
const double EnemyRotation::EnemyOmega = 0.02;
const double EnemyRotation::Radius = 24.0;
const double EnemyRotation::Hp = 5.0;
const int EnemyRotation::Score = 100;
const unsigned int EnemyRotation::Color = 0xFF0088;


EnemyRotation::EnemyRotation(double _x, double _y) :
	IEnemy(_x, _y, 0.0, 0.0, Radius, Hp, Score, Color)
{
}

void EnemyRotation::move() {
	double angle = elapsedFrame * 0.02;
	vx = 1.0 * cos(angle);
	vy = 1.0 * sin(angle);
	x += vx;
	y += vy;
}

void EnemyRotation::shot() {
	// 4•ûŒü‚ÉƒVƒ‡ƒbƒg‚ðŒ‚‚Â
	if (elapsedFrame % EnemyshotRate == 0) {
		for (size_t i = 0; i < EnemyshotNum; i++) {
			double rate = (double)i / (double)EnemyshotNum;
			double fx = EnemyBulletSpeed *cos(PI2 * rate);
			double fy = EnemyBulletSpeed * sin(PI2 * rate);
			gameManager.enemyBulletManager.add(std::make_shared<EnemyBullet>(x, y, fx, fy));
		}
	}
}

