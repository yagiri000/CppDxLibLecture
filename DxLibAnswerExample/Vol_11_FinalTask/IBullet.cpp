#include "DxLib.h"
#include "IBullet.h"


IBullet::IBullet(double _x, double _y, double _vx, double _vy, double _radius, double _attack, unsigned int _color, int _lifeTime) :
	x(_x), y(_y),
	vx(_vx), vy(_vy),
	radius(_radius),
	attack(_attack),
	color(_color),
	lifeTime(_lifeTime),
	elapsedFrame(0),
	isDead(false)
{
}

void IBullet::update() {
	checkDead();
	move();
	elapsedFrame++;
}

void IBullet::move() {
	x += vx; y+= vy;
}

void IBullet::checkDead() {
	if (elapsedFrame > lifeTime) {
		isDead = true;
	}
}

void IBullet::draw() const {
	DrawCircle(x, y, radius, color);
}
