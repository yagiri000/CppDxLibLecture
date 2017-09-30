#pragma once
#include "DxLib.h"

class Enemy {
public:
	double x, y;
	double vx, vy;
	Enemy(const Vec2& _pos);
	void update();
	void draw();
};