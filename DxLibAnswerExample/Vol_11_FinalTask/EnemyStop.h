#pragma once
#include "IEnemy.h"

class EnemyStop : public IEnemy {
public:
	static const size_t EnemyshotRate;
	static const double BulletSpeed;
	static const double Radius;
	static const double Hp;
	static const int Score;
	static const unsigned int Color;

	EnemyStop(double _x, double _y);
	~EnemyStop() = default;
	void move() override;
	void shot() override;
};