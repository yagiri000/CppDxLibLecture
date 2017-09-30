#include <iostream>
#include <algorithm>
#include "GameManager.h"

const size_t IEnemy::EffectNum = 25;
const double IEnemy::EffectGenerateRange = 64.0;

const double EnemyStalker::StalkerEnemySpeed = 1.5;
const double EnemyStalker::Radius = 24.0;
const double EnemyStalker::Hp = 5.0;
const int EnemyStalker::Score = 100;
const Color EnemyStalker::Color_(255, 0, 0);

const size_t EnemyStop::EnemyshotRate = 60;
const double EnemyStop::BulletSpeed = 1.0;
const double EnemyStop::Radius = 24.0;
const double EnemyStop::Hp = 5.0;
const int EnemyStop::Score = 100;
const Color EnemyStop::Color_(255, 128, 0);

const size_t EnemyRotation::EnemyshotRate = 120;
const size_t EnemyRotation::EnemyshotNum = 4;
const double EnemyRotation::EnemyBulletSpeed = 8.0;
const double EnemyRotation::EnemyOmega = 0.02;
const double EnemyRotation::Radius = 24.0;
const double EnemyRotation::Hp = 5.0;
const int EnemyRotation::Score = 100;
const Color EnemyRotation::Color_(255, 0, 128);


//敵の基底クラス
IEnemy::IEnemy(const Vec2 & _pos, const Vec2 & _velocity, double _radius, double _hp, int _score, const Color& _color) :
	x(_x), y(_y),
	velocity(_velocity),
	radius(_radius),
	hp(_hp),
	score(_score),
	color(_color),
	eFrame(0),
	isDead(false)
{
}

void IEnemy::update() {
	move();
	shot();
	checkHit();
	checkDead();
	eFrame++;
}

void IEnemy::draw() const {
	Circle(pos, radius).draw(color);
}


void IEnemy::checkHit() {
	for (const auto& bullet : gameManager.playerBulletManager.playerBullets) {
		// それぞれのプレイヤーの弾との当たり判定を取る
		if (Circle(pos, radius).intersects(Circle(bullet->pos, bullet->Radius)) && bullet->isDead == false) {
			hp -= bullet->Attack;
			gameManager.effectManager.add(std::make_shared<WhiteCircle>(bullet->pos));
			bullet->isDead = true;
		}
	}
}

void IEnemy::checkDead() {
	// 画面外に行ったかを確認
	// 敵の円状の当たり判定と、画面サイズ分の四角の当たり判定から画面内にいるか判定している
	if (!Circle(pos, radius).intersects(Rect(Window::Size()))) {
		isDead = true;
	}
	//HPがゼロかを確認
	if (hp < 1e-10) {
		// ゼロだったらスコアを加算
		gameManager.scoreManager.addScore(score);
		// エフェクト生成
		for (size_t j = 0; j < EffectNum; j++) {
			gameManager.effectManager.add(std::make_shared<WhiteCircle>(pos + Random(0.0, EffectGenerateRange) * RandomVec2()));
		}
		isDead = true;
	}
}



EnemyStalker::EnemyStalker(const Vec2 & _pos) :
	IEnemy(_pos, Vec2(), Radius, Hp, Score, Color_)
{
}

void EnemyStalker::move() {
	velocity = StalkerEnemySpeed * (gameManager.player.pos - pos).normalized();
	x += vx; y+= vy;
}

void EnemyStalker::shot() {
}



EnemyStop::EnemyStop(const Vec2 & _pos) :
	IEnemy(_pos, Vec2(), Radius, Hp, Score, Color_)
{
}

void EnemyStop::move() {
	velocity = Vec2(0.0, 0.0);
	x += vx; y+= vy;
}

void EnemyStop::shot() {
	// プレイヤーに向けてショットを撃つ
	if (eFrame % EnemyshotRate == 0) {
		Vec2 firstVel = BulletSpeed * (gameManager.player.pos - pos).normalized();
		gameManager.enemyBulletManager.add(std::make_shared<EnemyBullet>(pos, firstVel));
	}
}



EnemyRotation::EnemyRotation(const Vec2 & _pos) :
	IEnemy(_pos, Vec2(), Radius, Hp, Score, Color_)
{
}

void EnemyRotation::move() {
	velocity = Vec2(1.0, 0.0).rotate(eFrame * EnemyOmega);
	x += vx; y+= vy;
}

void EnemyRotation::shot() {
	// 4方向にショットを撃つ
	if (eFrame % EnemyshotRate == 0) {
		for (size_t i = 0; i < EnemyshotNum; i++) {
			Vec2 firstVel = Vec2(EnemyBulletSpeed, 0).rotated(TwoPi * i / EnemyshotNum);
			gameManager.enemyBulletManager.add(std::make_shared<EnemyBullet>(pos, firstVel));
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
