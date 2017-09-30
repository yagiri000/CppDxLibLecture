#pragma once
#include <vector>
#include <memory>
#include "DxLib.h"


//各敵の基底クラス
class IEnemy {
public:
	static const size_t EffectNum;
	static const double EffectGenerateRange;

	double x, y;
	double vx, vy;
	double radius;
	double hp;
	int score;
	unsigned int color;
	int elapsedFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	IEnemy(double _x, double _y, double _vx, double _vy, double _radius, double _hp, int _score, unsigned int _Color);

	virtual ~IEnemy() = default;

	void update();

	// 動き方
	virtual void move() = 0;

	// ショットの打ち方
	virtual void shot() = 0;

	// 自機が撃った弾との当たり判定を取る
	void checkHit();

	// 画面外に出ていないか、HPはゼロになっていないかをチェックし、死んでいるかどうかのフラグを更新する。
	void checkDead();

	void draw() const;
};


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

//敵全体を管理するクラス
class EnemyManager {
public:
	std::vector<std::shared_ptr<IEnemy>> enemies;
	EnemyManager();
	void add(const std::shared_ptr<IEnemy>& ptr);
	void update();
	void draw() const;
};

