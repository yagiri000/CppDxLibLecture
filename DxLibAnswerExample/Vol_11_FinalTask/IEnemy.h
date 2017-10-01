#pragma once


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





