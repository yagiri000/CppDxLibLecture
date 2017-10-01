#pragma once
#include <vector>
#include "PlayerBullet.h"

class PlayerBulletManager {
public:
	std::vector<PlayerBullet> playerBullets;
	PlayerBulletManager();
	void add(const PlayerBullet& ins);
	void update();
	void draw() const;
};
