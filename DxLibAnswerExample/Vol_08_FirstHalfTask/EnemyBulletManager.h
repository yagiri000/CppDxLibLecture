#pragma once
#include <vector>
#include "EnemyBullet.h"

class EnemyBulletManager {
public:
	std::vector<EnemyBullet> enemyBullets;
	EnemyBulletManager();

	// ¶¬‚µ‚½’e‚ğ’Ç‰Á
	void add(const EnemyBullet& ins);
	void update();
	void draw() const;
};
