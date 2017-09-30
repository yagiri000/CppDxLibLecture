#pragma once
#include <vector>
#include <memory>
#include "DxLib.h"


// 弾の基底クラス
class IBullet {
public:
	double x, y;
	double vx, vy;
	double radius;
	double attack;
	Color color;
	int lifeTime;
	int eFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	IBullet(const Vec2& _pos, const Vec2& _velocity, double _radius, double attack, const Color& _color, int _lifeTime);
	void update();
	void move();
	void checkDead();
	void draw() const;
	virtual ~IBullet() = default;
};

// プレイヤーの弾
class PlayerBullet : public IBullet{
public:
	static const double Radius;
	static const double Attack;
	static const Color Color_;
	static const int LifeTime;
	
	PlayerBullet(const Vec2& _pos, const Vec2& _velocity);
	~PlayerBullet() = default;
};

// 敵の弾
class EnemyBullet : public IBullet{
public:
	static const double Radius;
	static const double Attack;
	static const Color Color_;
	static const int LifeTime;

	EnemyBullet(const Vec2& _pos, const Vec2& _velocity);
	~EnemyBullet() = default;
};


// 敵の弾を管理するクラス
class EnemyBulletManager {
public:
	std::vector<std::shared_ptr<EnemyBullet>> enemyBullets;
	EnemyBulletManager();
	void add(const std::shared_ptr<EnemyBullet>& ptr);
	void update();
	void draw() const;
};

// プレイヤーの弾を管理するクラス
class PlayerBulletManager{
public:
	std::vector<std::shared_ptr<PlayerBullet>> playerBullets;
	PlayerBulletManager();
	void add(const std::shared_ptr<PlayerBullet>& ptr);
	void update();
	void draw() const;
};
