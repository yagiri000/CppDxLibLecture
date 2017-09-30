#include <iostream>
#include <algorithm>
#include "GameManager.h"
#include "MyGlobal.h"

const size_t IEnemy::EffectNum = 25;
const double IEnemy::EffectGenerateRange = 64.0;

const double EnemyStalker::StalkerEnemySpeed = 1.5;
const double EnemyStalker::Radius = 24.0;
const double EnemyStalker::Hp = 5.0;
const int EnemyStalker::Score = 100;
const unsigned int EnemyStalker::Color = 0xFF0000;

const size_t EnemyStop::EnemyshotRate = 60;
const double EnemyStop::BulletSpeed = 1.0;
const double EnemyStop::Radius = 24.0;
const double EnemyStop::Hp = 5.0;
const int EnemyStop::Score = 100;
const unsigned int EnemyStop::Color = 0xFF8800;

const size_t EnemyRotation::EnemyshotRate = 120;
const size_t EnemyRotation::EnemyshotNum = 4;
const double EnemyRotation::EnemyBulletSpeed = 8.0;
const double EnemyRotation::EnemyOmega = 0.02;
const double EnemyRotation::Radius = 24.0;
const double EnemyRotation::Hp = 5.0;
const int EnemyRotation::Score = 100;
const unsigned int EnemyRotation::Color = 0xFF0088;


//敵の基底クラス
IEnemy::IEnemy(double _x, double _y, double _vx, double _vy, double _radius, double _hp, int _score, unsigned int _color) :
	x(_x), y(_y),
	vx(_vx), vy(_vy),
	radius(_radius),
	hp(_hp),
	score(_score),
	color(_color),
	elapsedFrame(0),
	isDead(false)
{
}

void IEnemy::update() {
	move();
	shot();
	checkHit();
	checkDead();
	elapsedFrame++;
}

void IEnemy::draw() const {
	DrawCircle(x, y, radius, color);
}


void IEnemy::checkHit() {
	for (const auto& bullet : gameManager.playerBulletManager.playerBullets) {
		// それぞれのプレイヤーの弾との当たり判定を取る
		if (checkHitCircles(x, y, radius, bullet->x, bullet->y, bullet->radius) && bullet->isDead == false) {
			hp -= bullet->Attack;
			gameManager.effectManager.add(std::make_shared<WhiteCircle>(bullet->x, bullet->y));
			bullet->isDead = true;
		}
	}
}

void IEnemy::checkDead() {
	// 画面外に行ったかを確認
	// 敵の円状の当たり判定と、画面サイズ分の四角の当たり判定から画面内にいるか判定している
	//if (!Circle(pos, radius).intersects(Rect(Window::Size()))) {
	if (!checkHitPointRect(x, y, 0.0, 0.0, 640.0, 480.0)) {
		isDead = true;
	}
	//HPがゼロかを確認
	if (hp < 1e-10) {
		// ゼロだったらスコアを加算
		gameManager.scoreManager.addScore(score);
		// エフェクト生成
		for (size_t j = 0; j < EffectNum; j++) {
			double ix, iy;
			randomInCircle(EffectGenerateRange, &ix, &iy);
			gameManager.effectManager.add(std::make_shared<WhiteCircle>(x + ix, y + iy));
		}
		isDead = true;
	}
}



EnemyStalker::EnemyStalker(double _x, double _y) :
	IEnemy(_x, _y, 0.0, 0.0, Radius, Hp, Score, Color)
{
}

void EnemyStalker::move() {
	Player& player = gameManager.player;
	normalize(x, y, player.x, player.y, &vx, &vy);
	vx *= StalkerEnemySpeed;
	vy *= StalkerEnemySpeed;
	x += vx;
	y += vy;
}

void EnemyStalker::shot() {
}



EnemyStop::EnemyStop(double _x, double _y) :
	IEnemy(_x, _y, 0.0, 0.0, Radius, Hp, Score, Color)
{
}

void EnemyStop::move() {
	vx = 0.0;
	vy = 0.0;
	x += vx;
	y += vy;
}

void EnemyStop::shot() {
	// プレイヤーに向けてショットを撃つ
	if (elapsedFrame % EnemyshotRate == 0) {
		double bx, by;
		Player& p = gameManager.player;
		normalize(x, y, p.x, p.y, &bx, &by);
		bx *= BulletSpeed;
		by *= BulletSpeed;
		gameManager.enemyBulletManager.add(std::make_shared<EnemyBullet>(x, y, bx, by));
	}
}



EnemyRotation::EnemyRotation(double _x, double _y) :
	IEnemy(_x, _y, 0.0, 0.0, Radius, Hp, Score, Color)
{
}

void EnemyRotation::move() {
	double angle = elapsedFrame * 0.02;
	vx = 1.0 * cos(angle);
	vy = 1.0 * sin(angle);
	x += vx;
	y += vy;
}

void EnemyRotation::shot() {
	// 4方向にショットを撃つ
	if (elapsedFrame % EnemyshotRate == 0) {
		for (size_t i = 0; i < EnemyshotNum; i++) {
			double rate = (double)i / (double)EnemyshotNum;
			double fx = EnemyBulletSpeed *cos(PI2 * rate);
			double fy = EnemyBulletSpeed * sin(PI2 * rate);
			gameManager.enemyBulletManager.add(std::make_shared<EnemyBullet>(x, y, fx, fy));
		}
	}
}




EnemyManager::EnemyManager() {
}

void EnemyManager::add(const std::shared_ptr<IEnemy>& ptr) {
	enemies.emplace_back(ptr);
}

void EnemyManager::update() {
	for (const auto& enemy : enemies) {
		enemy->update();
	}

	auto iter = std::remove_if(enemies.begin(), enemies.end(), [](const std::shared_ptr<IEnemy>& ptr) {
		return ptr->isDead;
	});
	enemies.erase(iter, enemies.end());
}

void EnemyManager::draw() const {
	for (const auto& enemy : enemies) {
		enemy->draw();
	}
}
