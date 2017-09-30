#include <iostream>
#include <algorithm>
#include "Bullet.h"


const double PlayerBullet::Radius = 4.0;
const double PlayerBullet::Attack = 1.0;
const Color PlayerBullet::Color_(0, 0, 200);
const int PlayerBullet::LifeTime = 60;

const double EnemyBullet::Radius = 8.0;
const double EnemyBullet::Attack = 1.0;
const Color EnemyBullet::Color_(255, 255, 255);
const int EnemyBullet::LifeTime = 900;


IBullet::IBullet(const Vec2 & _pos, const Vec2 & _velocity, double _radius, double _attack, const Color & _color, int _lifeTime) :
	x(_x), y(_y),
	velocity(_velocity),
	radius(_radius),
	attack(_attack),
	color(_color),
	lifeTime(_lifeTime),
	eFrame(0),
	isDead(false)
{
}

void IBullet::update() {
	checkDead();
	move();
	eFrame++;
}

void IBullet::move() {
	x += vx; y+= vy;
}

void IBullet::checkDead() {
	if (eFrame > lifeTime) {
		isDead = true;
	}
}

void IBullet::draw() const {
	Circle(pos, radius).draw(color);
}


PlayerBullet::PlayerBullet(const Vec2& _pos, const Vec2& _velocity) :
	IBullet(_pos, _velocity, Radius, Attack, Color_, LifeTime)
{
}

EnemyBullet::EnemyBullet(const Vec2& _pos, const Vec2& _velocity) :
	IBullet(_pos, _velocity, Radius, Attack, Color_, LifeTime)
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

