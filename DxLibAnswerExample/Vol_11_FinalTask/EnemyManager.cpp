#include <algorithm>
#include "EnemyManager.h"

EnemyManager::EnemyManager() {
}

void EnemyManager::add(const std::shared_ptr<IEnemy>& ptr) {
	enemies.emplace_back(ptr);
}

void EnemyManager::update() {
	for (const auto& enemy : enemies) {
		enemy->update();
	}

	auto iter = std::remove_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<IEnemy>& ptr) {
		return ptr->isDead;
	});
	enemies.erase(iter, enemies.end());
}

void EnemyManager::draw() const {
	for (const auto& enemy : enemies) {
		enemy->draw();
	}
}