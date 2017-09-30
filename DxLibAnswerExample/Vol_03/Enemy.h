#pragma once
#include "DxLib.h"

class Enemy {
public:
	double x, y;
	double vx, vy;
	Enemy(double _x, double _y);
	void update();
	void draw();
};