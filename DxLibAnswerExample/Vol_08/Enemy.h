#pragma once
#include "DxLib.h"

class Enemy {
public:
	static const double Radius;

	// 敵の種類を設定
	enum Kind
	{
		Stalker,
		Rotation,
		Straight
	};
	Kind kind;
	double x, y;
	double vx, vy;
	int elapsedFrame;
	Enemy(double _x, double _y, Kind _kind);
	void update();
	void draw();
};
