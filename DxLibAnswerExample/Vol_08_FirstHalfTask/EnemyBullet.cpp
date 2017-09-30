#include <iostream>
#include <algorithm>
#include "EnemyBullet.h"

const double EnemyBullet::Radius = 8.0;
const Color EnemyBullet::Color_(255, 255, 255);
const int EnemyBullet::LifeTime = 900;

EnemyBullet::EnemyBullet(const Vec2 & _pos, const Vec2 & _velocity) :
	x(_x), y(_y),
	velocity(_velocity),
	eFrame(0),
	isDead(false)
{
}

void EnemyBullet::update() {
	checkDead();
	move();
	eFrame++;
}

void EnemyBullet::move() {
	x += vx; y+= vy;
}

void EnemyBullet::checkDead() {
	if (eFrame > LifeTime) {
		isDead = true;
	}
}

void EnemyBullet::draw() const {
	Circle(pos, Radius).draw(Color_);
}


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

