#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager {
private:
	void checkDelete(); // ‰æ–ÊŠO‚Ì“Gíœ
public:
	std::vector<Enemy> enemies;
	void update();
	void draw() const;
	void add(const Enemy& ins);
	size_t getEnemyNum();
};