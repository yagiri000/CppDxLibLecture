#pragma once
#include <vector>
#include <memory>
#include "PlayerBullet.h"

// プレイヤーの弾を管理するクラス
class PlayerBulletManager {
public:
	std::vector<std::shared_ptr<PlayerBullet>> playerBullets;
	PlayerBulletManager();
	void add(const std::shared_ptr<PlayerBullet>& ptr);
	void update();
	void draw() const;
};
