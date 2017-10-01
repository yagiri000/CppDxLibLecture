#pragma once

// エフェクトの基底クラス
class IEffect {
public:
	double x, y;
	int lifeTime;
	int elapsedFrame;
	bool isDead;

	IEffect(double _x, double _y, int _lifeTime);
	virtual ~IEffect() = default;
	virtual void update();
	virtual void draw() const = 0;

	// 死んでいるかどうかのフラグを更新
	void checkDead();
};
