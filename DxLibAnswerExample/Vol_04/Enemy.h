#pragma once
#include "DxLib.h"
#include "Player.h"

class Enemy {
public:
	double x, y;
	double vx, vy;
	Player *playerPtr;
	Enemy(double _x, double _y);
	void update();
	void draw();

	// プレイヤーへのポインタを取得する関数
	void setPlayerPtr(Player *ptr_);
};