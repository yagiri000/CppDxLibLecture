#pragma once
#include <vector>
#include "DxLib.h"

class EnemyBullet{
public:
	static const double Radius;
	static const Color Color_;
	static const int LifeTime;

	double x, y;
	double vx, vy;
	int eFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	EnemyBullet(const Vec2& _pos, const Vec2& _velocity);
	void update();
	void move();
	void checkDead();
	void draw() const;
};


class EnemyBulletManager{
public:
	std::vector<EnemyBullet> enemyBullets;
	EnemyBulletManager();

	// 生成した弾を追加
	void add(const EnemyBullet& ins);
	void update();
	void draw() const;
};
