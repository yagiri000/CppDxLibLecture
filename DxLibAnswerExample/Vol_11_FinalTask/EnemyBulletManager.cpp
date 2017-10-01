#include <algorithm>
#include "EnemyBulletManager.h"

EnemyBulletManager::EnemyBulletManager() {
}

void EnemyBulletManager::add(const std::shared_ptr<EnemyBullet>& ptr) {
	enemyBullets.emplace_back(ptr);
}

void EnemyBulletManager::update() {
	for (const auto& enemyBullet : enemyBullets) {
		enemyBullet->update();
	}

	auto iter = std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](const std::shared_ptr<EnemyBullet>& ptr) {
		return ptr->isDead;
	});
	enemyBullets.erase(iter, enemyBullets.end());
}

void EnemyBulletManager::draw() const {
	for (const auto& enemyBullet : enemyBullets) {
		enemyBullet->draw();
	}
}

