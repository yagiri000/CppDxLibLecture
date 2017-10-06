#include "EnemyManager.h"

void EnemyManager::update()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].update();
	}
}

void EnemyManager::draw()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].draw();
	}
}

void EnemyManager::add(Enemy enemy)
{
	enemies.emplace_back(enemy);
}
