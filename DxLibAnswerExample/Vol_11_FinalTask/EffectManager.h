#pragma once
#include <vector>
#include <memory>
#include "IEffect.h"

//エフェクトを管理するクラス
class EffectManager {
public:
	std::vector<std::shared_ptr<IEffect>> effects;
	EffectManager();
	void add(const std::shared_ptr<IEffect>& ptr);
	void update();
	void draw() const;
};

