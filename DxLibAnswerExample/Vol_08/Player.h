#pragma once
#include "DxLib.h"

class Player {
public:
	static const double Speed;
	double x, y;
	Player();
	void update();
	void draw();
};