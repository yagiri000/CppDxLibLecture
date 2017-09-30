#include <iostream>
#include <algorithm>
#include "Bullet.h"


const double PlayerBullet::Radius = 4.0;
const double PlayerBullet::Attack = 1.0;
const unsigned int PlayerBullet::Color = 0x0000AA;
const int PlayerBullet::LifeTime = 60;

const double EnemyBullet::Radius = 8.0;
const double EnemyBullet::Attack = 1.0;
const unsigned int EnemyBullet::Color = 0xFFFFFF;
const int EnemyBullet::LifeTime = 900;


IBullet::IBullet(double _x, double _y, double _vx, double _vy, double _radius, double _attack, unsigned int _color, int _lifeTime) :
	x(_x), y(_y),
	vx(_vx), vy(_vy),
	radius(_radius),
	attack(_attack),
	color(_color),
	lifeTime(_lifeTime),
	elapsedFrame(0),
	isDead(false)
{
}

void IBullet::update() {
	checkDead();
	move();
	elapsedFrame++;
}

void IBullet::move() {
	x += vx; y+= vy;
}

void IBullet::checkDead() {
	if (elapsedFrame > lifeTime) {
		isDead = true;
	}
}

void IBullet::draw() const {
	DrawCircle(x, y, radius, color);
}


PlayerBullet::PlayerBullet(double _x, double _y, double _vx, double _vy) :
	IBullet(_x, _y, _vx, _vy, Radius, Attack, Color, LifeTime)
{
}

EnemyBullet::EnemyBullet(double _x, double _y, double _vx, double _vy) :
	IBullet(_x, _y, _vx, _vy, Radius, Attack, Color, LifeTime)
{
}



PlayerBulletManager::PlayerBulletManager() {
}

void PlayerBulletManager::add(const std::shared_ptr<PlayerBullet>& ptr) {
	playerBullets.emplace_back(ptr);
}

void PlayerBulletManager::update() {
	for (const auto& playerBullet : playerBullets) {
		playerBullet->update();
	}

	//óvëfÇÃè¡ãé
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

