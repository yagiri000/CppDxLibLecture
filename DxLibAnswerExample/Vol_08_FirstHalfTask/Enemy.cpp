#include <iostream>
#include <algorithm>
#include "GameManager.h"

const double Enemy::Radius = 24.0;
const int Enemy::Score = 100;
const size_t Enemy::StopEnemyshotRate = 60;
const double Enemy::StopEnemyBulletSpeed = 1.0;
const size_t Enemy::RotationEnemyshotRate = 120;
const size_t Enemy::RotationEnemyshotNum = 4;
const double Enemy::RotationEnemyBulletSpeed = 8.0;
const size_t Enemy::EffectNum = 25;
const double Enemy::EffectGenerateRange = 64.0;
const double Enemy::StalkerEnemySpeed = 1.5;
const double Enemy::RotationEnemyOmega = 0.02;
const Color Enemy::EnemyStalkerColor(255, 0, 0);
const Color Enemy::EnemyStopColor(255, 128, 0);
const Color Enemy::EnemyRotationColor(255, 0, 128);


//敵の基底クラス
Enemy::Enemy(const Vec2 & _pos, Kind _kind) :
	x(_x), y(_y),
	velocity(),
	kind(_kind),
	hp(5.0),
	eFrame(0),
	isDead(false)
{
}

void Enemy::update() {
	move();
	shot();
	checkHit();
	checkDead();
	eFrame++;
}

void Enemy::draw() const {
	if (kind == Stalker) {
		Circle(pos, Radius).draw(EnemyStalkerColor);
	}
	else if (kind == Stop) {
		Circle(pos, Radius).draw(EnemyStopColor);
	}
	else if (kind == Rotation) {
		Circle(pos, Radius).draw(EnemyRotationColor);
	}
}

void Enemy::move() {
	if (kind == Stalker) {
		velocity = StalkerEnemySpeed * (gameManager.player.pos - pos).normalized();
	}
	else if (kind == Stop) {
		velocity = Vec2(0.0, 0.0);
	}
	else if (kind == Rotation) {
		velocity = Vec2(1.0, 0.0).rotate(eFrame * RotationEnemyOmega);
	}
	x += vx; y+= vy;
}

void Enemy::shot() {
	if (kind == Stalker) {

	}
	else if (kind == Stop) {
		// プレイヤーに向けてショットを撃つ
		if (eFrame % StopEnemyshotRate == 0) {
			Vec2 firstVel = StopEnemyBulletSpeed * (gameManager.player.pos - pos).normalized();
			gameManager.eBulletManager.add(EnemyBullet(pos, firstVel));
		}
	}
	else if (kind == Rotation) {
		// 4方向にショットを撃つ
		if (eFrame % RotationEnemyshotRate == 0) {
			for (size_t i = 0; i < RotationEnemyshotNum; i++) {
				Vec2 firstVel = Vec2(RotationEnemyBulletSpeed, 0).rotated(TwoPi * (double)i / (double)RotationEnemyshotNum);
				gameManager.eBulletManager.add(EnemyBullet(pos, firstVel));
			}
		}
	}
}


void Enemy::checkHit() {
	auto &vec = gameManager.pBulletManager.playerBullets;
	for (auto i = vec.begin(); i < vec.end(); i++) {
		// それぞれのプレイヤーの弾との当たり判定を取る
		if (Circle(pos, Radius).intersects(Circle(i->pos, i->Radius)) && i->isDead == false) {
			hp -= i->Attack;
			gameManager.effectManager.add(WhiteCircle(i->pos));
			i->isDead = true;
		}
	}
}

void Enemy::checkDead() {
	// 画面外に行ったかを確認
	// 敵の円状の当たり判定と、画面サイズ分の四角の当たり判定から画面内にいるか判定している
	if (!Circle(pos, Radius).intersects(Rect(Window::Size()))){
		isDead = true;
	}
	//HPがゼロかを確認
	if (hp < 1e-10) {
		// ゼロだったらスコアを加算
		gameManager.scoreManager.addScore(Score);
		// エフェクト生成
		for (size_t j = 0; j < EffectNum; j++) {
			gameManager.effectManager.add(WhiteCircle(pos + Random(0.0, EffectGenerateRange) * RandomVec2()));
		}
		isDead = true;
	}
}



EnemyManager::EnemyManager() {
}

void EnemyManager::add(const Enemy& ins) {
	enemies.emplace_back(ins);
}

void EnemyManager::update() {
	for (auto&& enemy : enemies) {
		enemy.update();
	}

	//要素の消去
	auto iter = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& ins) {
		return ins.isDead;
	});
	enemies.erase(iter, enemies.end());
}

void EnemyManager::draw() const {
	for (auto&& enemy : enemies) {
		enemy.draw();
	}
}

