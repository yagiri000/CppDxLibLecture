#pragma once


//白い円を一瞬描画するエフェクト
class WhiteCircleEffect{
public:
	static const int LifeTime;
	static const double Radius;
	static const unsigned int Color;

	double x, y;
	int elapsedFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	WhiteCircleEffect(double _x, double _y);
	void update();
	
	// 死んでいるかどうかのフラグを更新
	void checkDead();
	void draw() const;
};

