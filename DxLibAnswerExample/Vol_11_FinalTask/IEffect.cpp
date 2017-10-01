#include "IEffect.h"


IEffect::IEffect(double _x, double _y, int _lifeTime) :
	x(_x), y(_y),
	lifeTime(_lifeTime),
	elapsedFrame(0),
	isDead(false)
{
}

void IEffect::checkDead() {
	if (elapsedFrame > lifeTime) {
		isDead = true;
	}
}

void IEffect::update() {
	checkDead();
	elapsedFrame++;
}

