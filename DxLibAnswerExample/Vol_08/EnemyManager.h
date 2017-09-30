#pragma once
#include "Enemy.h"
#include <vector>

class EnemyManager {
private:
	std::vector<Enemy> enemies;
	void checkDelete(); // ‰æ–ÊŠO‚Ì“Gíœ
public:
	void update();
	void draw();
	void add(const Enemy& enemy);
	size_t getEnemyNum();
};