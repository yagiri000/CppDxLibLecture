#pragma once
#include "DxLib.h"

class Player {
public:
	double x, y;
	double speed;

	Player();
	void update();

	//自機（円）を描画
	void draw();
};