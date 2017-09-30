#pragma once
#include "DxLib.h"

class Enemy {
public:
	static const double Radius;

	// “G‚Ìí—Ş‚ğİ’è
	enum Kind
	{
		Stalker,
		Rotation,
		Straight
	};
	Kind kind;
	double x, y;
	double vx, vy;
	int eFrame;
	Enemy(const Vec2& _pos, Kind _kind);
	void update();
	void draw();
};
