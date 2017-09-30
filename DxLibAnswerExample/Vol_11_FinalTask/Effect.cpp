#include <iostream>
#include <algorithm>
#include "Effect.h"

const int WhiteCircle::LifeTime = 5;
const double WhiteCircle::Radius = 50.0;
const Color WhiteCircle::Color_(255, 255, 255, 80);



void IParticleEffect::checkDead() {
	if (eFrame > lifeTime) {
		isDead = true;
	}
}

void IParticleEffect::update() {
	checkDead();
	eFrame++;
}

WhiteCircle::WhiteCircle(const Vec2& _pos) :
	IParticleEffect(_pos, LifeTime)
{
}

void WhiteCircle::draw()const {
	Circle(pos, Radius).draw(Color_);
}


//エフェクトの管理クラス
EffectManager::EffectManager() {
}

void EffectManager::add(const std::shared_ptr<IParticleEffect>& ptr) {
	effects.emplace_back(ptr);
}

void EffectManager::update() {
	for (const auto& effect : effects) {
		effect->update();
	}

	auto iter = std::remove_if(effects.begin(), effects.end(), [](const std::shared_ptr<IParticleEffect>& ptr) {
		return ptr->isDead;
	});
	effects.erase(iter, effects.end());
}

void EffectManager::draw() const {
	for (const auto& effect : effects) {
		effect->draw();
	}
}

IParticleEffect::IParticleEffect(const Vec2 & _pos, int _lifeTime) :
	x(_x), y(_y),
	lifeTime(_lifeTime),
	eFrame(0),
	isDead(false)
{
}
