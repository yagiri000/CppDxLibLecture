#pragma once
#include <memory>
#include<Siv3D.hpp>


class Player {
public:
	static const double Radius;
	static const size_t FireRate;
	static const double MoveSpeed;
	static const Vec2 BulletFirstVelocity;
	static const Vec2 BulletFirstDelta;
	static const size_t EffectNum;
	static const double EffectRange;
	static const Color Color_;
	static const Vec2 FirstPos;

	double x, y;
	int fireCool;

	Player();
	void update();
	void draw() const;
	void move();
	void shot();
	void checkHit();
};
