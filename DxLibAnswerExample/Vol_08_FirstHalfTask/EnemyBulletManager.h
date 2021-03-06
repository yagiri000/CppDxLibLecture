#pragma once
#include <vector>
#include "EnemyBullet.h"

class EnemyBulletManager {
public:
	std::vector<EnemyBullet> enemyBullets;
	EnemyBulletManager();

	// 生成した弾を追加
	void add(const EnemyBullet& ins);
	void update();
	void draw() const;
};
