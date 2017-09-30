#include "DxLib.h"
#include "GameManager.h"

const double Player::Radius = 16;
const size_t Player::FireRate = 5;
const double Player::moveSpeed = 5.0;
const Vec2 Player::BulletFirstVelocity(0.0, -15.0);
const Vec2 Player::BulletFirstDelta(0.0, -20.0);
const size_t Player::EffectNum = 25;
const double Player::EffectRange = 64.0;
const Color Player::Color_(0, 0, 255);
const Vec2 Player::FirstPos(320.0, 400.0);

Player::Player() :
	pos(FirstPos),
	fireCool(0)
{
}

void Player::update() {
	move();
	shot();
	checkHit();
}

void Player::move() {
	// 上下左右キーで移動
	if (keyState[KEY_INPUT_LEFT] > 0) {
		x -= moveSpeed;
	}
	if (keyState[KEY_INPUT_RIGHT] > 0) {
		x += moveSpeed;
	}
	if (keyState[KEY_INPUT_UP] > 0) {
		y -= moveSpeed;
	}
	if (keyState[KEY_INPUT_DOWN] > 0) {
		y += moveSpeed;
	}
}

void Player::shot() {
	fireCool++;
	if (Input::KeyZ.pressed) {
		if (fireCool >= FireRate) {
			gameManager.pBulletManager.add(PlayerBullet(pos + BulletFirstDelta, BulletFirstVelocity));
			fireCool = 0;
		}
	}
}

void Player::checkHit() {
	//敵弾から自機への当たり判定
	for (auto i = gameManager.eBulletManager.enemyBullets.begin(); i < gameManager.eBulletManager.enemyBullets.end(); i++) {
		if (Circle(pos, Radius).intersects(Circle(i->pos, i->Radius)) && i->isDead == false) {
			// エフェクト生成
			for (size_t j = 0; j < EffectNum; j++) {
				gameManager.effectManager.add(WhiteCircle(pos + Random(0.0, EffectRange) * RandomVec2()));
			}
			// スコア加算
			gameManager.scoreManager.addDamagedNum();
			i->isDead = true;
		}
	}

	//敵自身から自機への当たり判定
	for (auto i = gameManager.enemyManager.enemies.begin(); i < gameManager.enemyManager.enemies.end(); i++) {
		if (Circle(pos, Radius).intersects(Circle(i->pos, i->Radius)) && i->isDead == false) {
			// エフェクト生成
			for (size_t j = 0; j < EffectNum; j++) {
				gameManager.effectManager.add(WhiteCircle(pos + Random(0.0, EffectRange) * RandomVec2()));
			}
			// スコア加算
			gameManager.scoreManager.addDamagedNum();
			i->isDead = true;
		}
	}
}

void Player::draw() const {
	Circle(pos, Radius).draw(Color_);
}