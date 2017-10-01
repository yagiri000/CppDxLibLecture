#include <algorithm>
#include "DxLib.h"
#include "EnemyBulletManager.h"

EnemyBulletManager::EnemyBulletManager() {
}

void EnemyBulletManager::add(const EnemyBullet& ins) {
	enemyBullets.emplace_back(ins);
}

void EnemyBulletManager::update() {
	for (auto&& enemyBullet : enemyBullets) {
		enemyBullet.update();
	}

	auto iter = std::remove_if(enemyBullets.begin(), enemyBullets.end(), [](const EnemyBullet& ins) {
		return ins.isDead;
	});
	enemyBullets.erase(iter, enemyBullets.end());
}

void EnemyBulletManager::draw() const {
	for (auto&& enemyBullet : enemyBullets) {
		enemyBullet.draw();
	}
}

