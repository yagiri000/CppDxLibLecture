#include "EnemyBullet.h"

const double EnemyBullet::Radius = 8.0;
const double EnemyBullet::Attack = 1.0;
const unsigned int EnemyBullet::Color = 0xFFFFFF;
const int EnemyBullet::LifeTime = 900;

EnemyBullet::EnemyBullet(double _x, double _y, double _vx, double _vy) :
	IBullet(_x, _y, _vx, _vy, Radius, Attack, Color, LifeTime)
{
}
