#include "MyGlobal.h"
#include "GameManager.h"
#include "EnemyStalker.h"

const double EnemyStalker::StalkerEnemySpeed = 1.5;
const double EnemyStalker::Radius = 24.0;
const double EnemyStalker::Hp = 5.0;
const int EnemyStalker::Score = 100;
const unsigned int EnemyStalker::Color = 0xFF0000;

EnemyStalker::EnemyStalker(double _x, double _y) :
	IEnemy(_x, _y, 0.0, 0.0, Radius, Hp, Score, Color)
{
}

void EnemyStalker::move() {
	Player& player = gameManager.player;
	normalize(x, y, player.x, player.y, &vx, &vy);
	vx *= StalkerEnemySpeed;
	vy *= StalkerEnemySpeed;
	x += vx;
	y += vy;
}

void EnemyStalker::shot() {
}
