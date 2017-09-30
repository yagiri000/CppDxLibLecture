#pragma once
#include <vector>
#include "DxLib.h"


//白い円を一瞬描画するエフェクト
class WhiteCircle{
public:
	static const int LifeTime;
	static const double Radius;
	static const unsigned int Color;

	double x, y;
	int elapsedFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	WhiteCircle(double _x, double _y);
	void update();
	
	// 死んでいるかどうかのフラグを更新
	void checkDead();
	void draw() const;
};


//エフェクトを管理するクラス
class EffectManager{
public:
	std::vector<WhiteCircle> effects;
	EffectManager();
	void add(const WhiteCircle& ins);
	void update();
	void draw() const;
};

