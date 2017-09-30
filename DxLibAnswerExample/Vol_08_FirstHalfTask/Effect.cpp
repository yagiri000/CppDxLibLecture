#include <iostream>
#include <algorithm>
#include "Effect.h"

const int WhiteCircle::LifeTime = 5;
const double WhiteCircle::Radius = 50.0;
const Color WhiteCircle::Color(255, 255, 255, 80);


WhiteCircle::WhiteCircle(double _x, double _y) :
	x(_x), y(_y),
	isDead(false),
	elapsedFrame(0)
{
}

void WhiteCircle::update() {
	checkDead();
	elapsedFrame++;
}


void WhiteCircle::checkDead() {
	if (elapsedFrame > LifeTime) {
		isDead = true;
	}
}

void WhiteCircle::draw()const {
	DrawCircle(x, y, Radius, Color);
}


//エフェクトの管理クラス
EffectManager::EffectManager() {
}

void EffectManager::add(const WhiteCircle& ins) {
	effects.emplace_back(ins);
}

void EffectManager::update() {
	for (auto&& effect : effects) {
		effect.update();
	}

	auto iter = std::remove_if(effects.begin(), effects.end(), [](const WhiteCircle& ins) {
		return ins.isDead;
	});
	effects.erase(iter, effects.end());
}

void EffectManager::draw() const {
	for (auto&& effect : effects) {
		effect.draw();
	}
}

