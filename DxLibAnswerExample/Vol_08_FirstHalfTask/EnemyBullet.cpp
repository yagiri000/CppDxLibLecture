#include <iostream>
#include <algorithm>
#include "EnemyBullet.h"

const double EnemyBullet::Radius = 8.0;
const unsigned int EnemyBullet::Color = 0xFFFFFF;
const int EnemyBullet::LifeTime = 900;

EnemyBullet::EnemyBullet(double _x, double _y, double _vx, double _vy) :
	x(_x), y(_y),
	vx(_vx), vy(_vy),
	elapsedFrame(0),
	isDead(false)
{
}

void EnemyBullet::update() {
	checkDead();
	move();
	elapsedFrame++;
}

void EnemyBullet::move() {
	x += vx; y+= vy;
}

void EnemyBullet::checkDead() {
	if (elapsedFrame > LifeTime) {
		isDead = true;
	}
}

void EnemyBullet::draw() const {
	DrawCircle(x, y, Radius, Color);
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

