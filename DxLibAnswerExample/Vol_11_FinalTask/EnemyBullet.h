#pragma once
#include "IBullet.h"

// “G‚Ì’e
class EnemyBullet : public IBullet {
public:
	static const double Radius;
	static const double Attack;
	static const unsigned int Color;
	static const int LifeTime;

	EnemyBullet(double _x, double _y, double _vx, double _vy);
	~EnemyBullet() = default;
};