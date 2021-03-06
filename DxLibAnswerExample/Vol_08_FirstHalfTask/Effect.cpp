#include <iostream>
#include "DxLib.h"
#include "Effect.h"

const int WhiteCircleEffect::LifeTime = 5;
const double WhiteCircleEffect::Radius = 50.0;
const unsigned int WhiteCircleEffect::Color = 0xFFFFFF;


WhiteCircleEffect::WhiteCircleEffect(double _x, double _y) :
	x(_x), y(_y),
	isDead(false),
	elapsedFrame(0)
{
}

void WhiteCircleEffect::update() {
	checkDead();
	elapsedFrame++;
}


void WhiteCircleEffect::checkDead() {
	if (elapsedFrame > LifeTime) {
		isDead = true;
	}
}

void WhiteCircleEffect::draw()const {
	// �����ȉ~��`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawCircle(x, y, Radius, Color);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

