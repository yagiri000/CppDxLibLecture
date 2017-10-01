#pragma once
#include "IEnemy.h"

class EnemyStalker : public IEnemy {
public:
	static const double StalkerEnemySpeed;
	static const double Radius;
	static const double Hp;
	static const int Score;
	static const unsigned int Color;

	EnemyStalker(double _x, double _y);
	~EnemyStalker() = default;
	void move() override;
	void shot() override;
};