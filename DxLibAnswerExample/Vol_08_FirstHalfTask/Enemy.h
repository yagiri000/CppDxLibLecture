#pragma once
#include <vector>
#include "DxLib.h"


//各敵の基底クラス
class Enemy{
public:
	// 敵の種類を表すenum
	enum Kind{
		Stalker,
		Stop,
		Rotation,
	};

	static const double Radius;
	static const int Score;
	static const size_t StopEnemyshotRate;
	static const double StopEnemyBulletSpeed;
	static const size_t RotationEnemyshotRate;
	static const size_t RotationEnemyshotNum;
	static const double RotationEnemyBulletSpeed;
	static const size_t EffectNum;
	static const double EffectGenerateRange;
	static const double StalkerEnemySpeed;
	static const double RotationEnemyOmega;
	static const unsigned int EnemyStalkerColor;
	static const unsigned int EnemyStopColor;
	static const unsigned int EnemyRotationColor;

	double x, y; 
	Kind kind; // 敵の種類
	double vx, vy;
	double hp;
	int elapsedFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	Enemy(double _x, double _y, Kind _kind);
	void update();
	void draw() const;
	void move();
	void shot();

	// 自機が撃った弾との当たり判定を取る
	void checkHit();

	// 画面外に出ていないか、HPはゼロになっていないかをチェックし、死んでいるかどうかのフラグを更新する。
	void checkDead();
};



//敵全体を管理するクラス
class EnemyManager{
public:
	std::vector<Enemy> enemies;
	EnemyManager();
	void add(const Enemy& ins);
	void update();
	void draw() const;
};

