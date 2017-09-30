#pragma once
#include<Siv3D.hpp>


class Player{
public:
	static const double Radius;
	static const size_t FireRate;
	static const double moveSpeed;
	static const Vec2 BulletFirstVelocity;
	static const Vec2 BulletFirstDelta;
	static const size_t EffectNum;
	static const double EffectRange;
	static const Color Color_;
	static const Vec2 FirstPos;

	Vec2 pos;
	int fireCool;

	Player();
	void update();
	void draw() const;
	void move();
	void shot();
	void checkHit();
};
