#pragma once
#include <vector>
#include "DxLib.h"
#include "Enemy.h"

class EnemyManager {
public:
	std::vector<Enemy> enemies;
	void update();
	void draw();
	void add(Enemy enemy);
};