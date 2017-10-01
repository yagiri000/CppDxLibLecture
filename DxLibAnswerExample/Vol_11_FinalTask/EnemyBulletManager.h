#pragma once
#include <vector>
#include <memory>
#include "EnemyBullet.h"

// “G‚Ì’e‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class EnemyBulletManager {
public:
	std::vector<std::shared_ptr<EnemyBullet>> enemyBullets;
	EnemyBulletManager();
	void add(const std::shared_ptr<EnemyBullet>& ptr);
	void update();
	void draw() const;
};