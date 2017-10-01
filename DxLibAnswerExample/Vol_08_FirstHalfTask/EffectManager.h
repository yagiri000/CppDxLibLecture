#pragma once
#include <vector>
#include "Effect.h"
#include "DxLib.h"

//エフェクトを管理するクラス
class EffectManager {
public:
	std::vector<WhiteCircleEffect> effects;
	EffectManager();
	void add(const WhiteCircleEffect& ins);
	void update();
	void draw() const;
};

