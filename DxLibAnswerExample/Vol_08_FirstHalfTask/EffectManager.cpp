#include <iostream>
#include <algorithm>
#include "EffectManager.h"

//エフェクトの管理クラス
EffectManager::EffectManager() {
}

void EffectManager::add(const WhiteCircleEffect& ins) {
	effects.emplace_back(ins);
}

void EffectManager::update() {
	for (auto&& effect : effects) {
		effect.update();
	}

	auto iter = std::remove_if(effects.begin(), effects.end(), [](const WhiteCircleEffect& ins) {
		return ins.isDead;
	});
	effects.erase(iter, effects.end());
}

void EffectManager::draw() const {
	for (auto&& effect : effects) {
		effect.draw();
	}
}

