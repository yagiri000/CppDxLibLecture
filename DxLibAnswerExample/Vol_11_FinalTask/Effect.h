#pragma once
#include <vector>
#include <memory>
#include <Siv3D.hpp>

// エフェクトの基底クラス
class IParticleEffect {
public:
	Vec2 pos;
	int lifeTime;
	int eFrame;
	bool isDead;

	IParticleEffect(const Vec2& _pos, int _lifeTime);
	virtual ~IParticleEffect() = default;
	virtual void update();
	virtual void draw() const = 0;

	// 死んでいるかどうかのフラグを更新
	void checkDead();
};

//白い円を一瞬描画するエフェクト
class WhiteCircle : public IParticleEffect{
public:
	static const int LifeTime;
	static const double Radius;
	static const Color Color_;

	WhiteCircle(const Vec2& _pos);
	~WhiteCircle() = default;
	void draw() const override;
};

//エフェクトを管理するクラス
class EffectManager{
public:
	std::vector<std::shared_ptr<IParticleEffect>> effects;
	EffectManager();
	void add(const std::shared_ptr<IParticleEffect>& ptr);
	void update();
	void draw() const;
};

