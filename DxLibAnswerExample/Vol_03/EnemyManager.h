#pragma once
#include <vector>
#include <Siv3D.hpp>
#include "Enemy.h"

class EnemyManager {
public:
	std::vector<Enemy> enemies;
	void update();
	void draw();
	void add(Enemy enemy);
};