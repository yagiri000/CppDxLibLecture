#include <algorithm>
#include "PlayerBulletManager.h"


PlayerBulletManager::PlayerBulletManager() {
}

void PlayerBulletManager::add(const std::shared_ptr<PlayerBullet>& ptr) {
	playerBullets.emplace_back(ptr);
}

void PlayerBulletManager::update() {
	for (const auto& playerBullet : playerBullets) {
		playerBullet->update();
	}

	//—v‘f‚ÌÁ‹
	auto iter = std::remove_if(playerBullets.begin(), playerBullets.end(), [](const std::shared_ptr<PlayerBullet>& ptr) {
		return ptr->isDead;
	});
	playerBullets.erase(iter, playerBullets.end());
}

void PlayerBulletManager::draw() const {
	for (const auto& playerBullet : playerBullets) {
		playerBullet->draw();
	}
}
