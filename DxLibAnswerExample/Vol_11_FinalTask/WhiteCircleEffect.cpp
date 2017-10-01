#include "WhiteCircleEffect.h"
#include "DxLib.h"

const int WhiteCircleEffect::LifeTime = 5;
const double WhiteCircleEffect::Radius = 50.0;
const unsigned int WhiteCircleEffect::Color = 0xFFFFFF;

WhiteCircleEffect::WhiteCircleEffect(double _x, double _y) :
	IEffect(_x, _y, LifeTime)
{
}

void WhiteCircleEffect::draw()const {
	// “§–¾‚È‰~‚ð•`‰æ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawCircle(x, y, Radius, Color);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}