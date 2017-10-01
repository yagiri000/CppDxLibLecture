#pragma once

// 弾の基底クラス
class IBullet {
public:
	double x, y;
	double vx, vy;
	double radius;
	double attack;
	unsigned int color;
	int lifeTime;
	int elapsedFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	IBullet(double _x, double _y, double _vx, double _vy, double _radius, double attack, unsigned int _color, int _lifeTime);
	void update();
	void move();
	void checkDead();
	void draw() const;
	virtual ~IBullet() = default;
};
