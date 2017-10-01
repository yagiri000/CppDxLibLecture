#include <iostream>
#include <algorithm>
#include "PlayerBulletManager.h"

PlayerBulletManager::PlayerBulletManager() {
}

void PlayerBulletManager::add(const PlayerBullet& ins) {
	playerBullets.emplace_back(ins);
}

void PlayerBulletManager::update() {
	for (auto&& playerBullet : playerBullets) {
		playerBullet.update();
	}

	//óvëfÇÃè¡ãé
	auto iter = std::remove_if(playerBullets.begin(), playerBullets.end(), [](const PlayerBullet& ins) {
		return ins.isDead;
	});
	playerBullets.erase(iter, playerBullets.end());
}

void PlayerBulletManager::draw() const {
	for (auto&& playerBullet : playerBullets) {
		playerBullet.draw();
	}
}

