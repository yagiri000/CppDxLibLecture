#include <algorithm>
#include "EffectManager.h"

//エフェクトの管理クラス
EffectManager::EffectManager() {
}

void EffectManager::add(const std::shared_ptr<IEffect>& ptr) {
	effects.emplace_back(ptr);
}

void EffectManager::update() {
	for (const auto& effect : effects) {
		effect->update();
	}

	auto iter = std::remove_if(effects.begin(), effects.end(), [](const std::shared_ptr<IEffect>& ptr) {
		return ptr->isDead;
	});
	effects.erase(iter, effects.end());
}

void EffectManager::draw() const {
	for (const auto& effect : effects) {
		effect->draw();
	}
}
