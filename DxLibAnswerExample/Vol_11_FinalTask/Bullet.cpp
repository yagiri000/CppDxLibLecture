#include <iostream>
#include <algorithm>
#include "Bullet.h"


const double PlayerBullet::Radius = 4.0;
const double PlayerBullet::Attack = 1.0;
const Color PlayerBullet::Color(0, 0, 200);
const int PlayerBullet::LifeTime = 60;

const double EnemyBullet::Radius = 8.0;
const double EnemyBullet::Attack = 1.0;
const Color EnemyBullet::Color(255, 255, 255);
const int EnemyBullet::LifeTime = 900;


IBullet::IBullet(double _x, double _y, const Vec2 & _velocity, double _radius, double _attack, const Color & _color, int _lifeTime) :
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
	Circle(pos, radius).draw(color);
}


PlayerBullet::PlayerBullet(double _x, double _y, double _vx, double _vy) :
	IBullet(_pos, _velocity, Radius, Attack, Color, LifeTime)
{
}

EnemyBullet::EnemyBullet(double _x, double _y, double _vx, double _vy) :
	IBullet(_pos, _velocity, Radius, Attack, Color, LifeTime)
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

	//�v�f�̏���
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
