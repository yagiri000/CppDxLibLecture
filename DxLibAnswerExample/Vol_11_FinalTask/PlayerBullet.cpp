#include "PlayerBullet.h"

const double PlayerBullet::Radius = 4.0;
const double PlayerBullet::Attack = 1.0;
const unsigned int PlayerBullet::Color = 0x0000AA;
const int PlayerBullet::LifeTime = 60;


PlayerBullet::PlayerBullet(double _x, double _y, double _vx, double _vy) :
	IBullet(_x, _y, _vx, _vy, Radius, Attack, Color, LifeTime)
{
}
