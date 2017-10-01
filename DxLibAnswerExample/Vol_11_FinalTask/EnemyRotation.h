#pragma once
#include "IEnemy.h"

class EnemyRotation : public IEnemy {
public:
	static const size_t EnemyshotRate;
	static const size_t EnemyshotNum;
	static const double EnemyBulletSpeed;
	static const double EnemyOmega;
	static const double Radius;
	static const double Hp;
	static const int Score;
	static const unsigned int Color;

	EnemyRotation(double _x, double _y);
	~EnemyRotation() = default;
	void move() override;
	void shot() override;
};

