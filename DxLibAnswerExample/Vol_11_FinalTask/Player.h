#pragma once
#include <memory>
#include "DxLib.h"


class Player {
public:
	static const double Radius;
	static const size_t FireRate;
	static const double MoveSpeed;
	static const double BulletFirstVelocityX;
	static const double BulletFirstVelocityY;
	static const double BulletFirstDeltaX;
	static const double BulletFirstDeltaY;
	static const size_t EffectNum;
	static const double EffectRange;
	static const unsigned int Color;
	static const double FirstPosX;
	static const double FirstPosY;

	double x, y;
	int fireCool;

	Player();
	void update();
	void draw() const;
	void move();
	void shot();
	void checkHit();
};
