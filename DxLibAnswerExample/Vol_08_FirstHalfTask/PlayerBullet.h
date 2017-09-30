#pragma once
#include <vector>
#include <Siv3D.hpp>

class PlayerBullet{
public:
	static const double Radius;
	static const double Attack;
	static const Color Color_;
	static const int LifeTime;

	Vec2 pos;
	Vec2 velocity;
	int eFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	PlayerBullet(const Vec2& _pos, const Vec2& _velocity);
	void update();
	void move();
	void checkDead();
	void draw() const;
};


class PlayerBulletManager{
public:
	std::vector<PlayerBullet> playerBullets;
	PlayerBulletManager();
	void add(const PlayerBullet& ins);
	void update();
	void draw() const;
};
