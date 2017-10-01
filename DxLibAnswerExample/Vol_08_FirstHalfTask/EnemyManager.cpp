#include <algorithm>
#include "EnemyManager.h"
#include "MyGlobal.h"

void EnemyManager::update() {
	for (auto&& enemy : enemies) {
		enemy.update();
	}
	checkDelete();
}

void EnemyManager::draw() const{
	for (const auto& enemy : enemies) {
		enemy.draw();
	}
}

void EnemyManager::add(const Enemy& ins)
{
	enemies.emplace_back(ins);
}

size_t EnemyManager::getEnemyNum(){
	return enemies.size();
}

void EnemyManager::checkDelete() {
	auto it = enemies.begin();

	auto rmvIter = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {
		return enemy.isDead;
	});

	enemies.erase(rmvIter, enemies.end());
}