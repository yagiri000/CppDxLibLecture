#pragma once
#include <vector>
#include <Siv3D.hpp>


//白い円を一瞬描画するエフェクト
class WhiteCircle{
public:
	static const int LifeTime;
	static const double Radius;
	static const Color Color_;

	Vec2 pos;
	int eFrame; // 生成されてからの経過フレーム
	bool isDead; // 死んでいるかどうかのフラグ

	WhiteCircle(const Vec2& _pos);
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

