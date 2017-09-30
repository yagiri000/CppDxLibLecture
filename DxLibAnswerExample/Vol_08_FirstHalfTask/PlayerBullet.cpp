#include <iostream>
#include <algorithm>
#include "PlayerBullet.h"

const double PlayerBullet::Radius = 4.0;
const double PlayerBullet::Attack = 1.0;
const Color PlayerBullet::Color_(0, 0, 200);
const int PlayerBullet::LifeTime = 60;

PlayerBullet::PlayerBullet(const Vec2 & _pos, const Vec2 & _velocity):
	pos(_pos),
	velocity(_velocity),
	eFrame(0),
	isDead(false)
{
}

void PlayerBullet::update() {
	checkDead();
	move();
	eFrame++;
}

void PlayerBullet::move() {
	pos += velocity;
}

void PlayerBullet::checkDead() {
	if (eFrame > LifeTime) {
		isDead = true;
	}
}

void PlayerBullet::draw() const {
	Circle(pos, Radius).draw(Color_);
}



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

