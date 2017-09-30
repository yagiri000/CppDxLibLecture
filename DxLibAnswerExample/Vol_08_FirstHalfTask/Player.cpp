#include "DxLib.h"
#include "MyGlobal.h"
#include "GameManager.h"

const double Player::Radius = 16;
const size_t Player::FireRate = 5;
const double Player::moveSpeed = 5.0;
const double Player::BulletFirstVelocityX = 0.0;
const double Player::BulletFirstVelocityY = -15.0;
const double Player::BulletFirstDeltaX = 0.0;
const double Player::BulletFirstDeltaY = -20.0;
const size_t Player::EffectNum = 25;
const double Player::EffectRange = 64.0;
const unsigned int Player::Color = 0x0000FF;
const double Player::FirstPosX = 320.0;
const double Player::FirstPosY = 400.0;

Player::Player() :
	x(FirstPosX),
	y(FirstPosY),
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
	if (keyState[KEY_INPUT_Z] > 0) {
		if (fireCool >= FireRate) {
			gameManager.pBulletManager.add(PlayerBullet(x + BulletFirstDeltaX, y + BulletFirstDeltaY, BulletFirstVelocityX, BulletFirstVelocityY));
			fireCool = 0;
		}
	}
}

void Player::checkHit() {
	//敵弾から自機への当たり判定
	for (auto i = gameManager.eBulletManager.enemyBullets.begin(); i < gameManager.eBulletManager.enemyBullets.end(); i++) {
		if (checkHitCircles(x, y, Radius, i->x, i->y, i->Radius) && i->isDead == false) {
			// エフェクト生成
			for (size_t j = 0; j < EffectNum; j++) {
				double ix, iy;
				randomInCircle(EffectRange, &ix, &iy);
				gameManager.effectManager.add(WhiteCircle(x + ix, y + iy));
			}
			// スコア加算
			gameManager.scoreManager.addDamagedNum();
			i->isDead = true;
		}
	}

	//敵自身から自機への当たり判定
	for (auto i = gameManager.enemyManager.enemies.begin(); i < gameManager.enemyManager.enemies.end(); i++) {
		if (checkHitCircles(x, y, Radius, i->x, i->y, i->Radius) && i->isDead == false) {
			// エフェクト生成
			for (size_t j = 0; j < EffectNum; j++) {
				double ix, iy;
				randomInCircle(EffectRange, &ix, &iy);
				gameManager.effectManager.add(WhiteCircle(x + ix, y + iy));
			}
			// スコア加算
			gameManager.scoreManager.addDamagedNum();
			i->isDead = true;
		}
	}
}

void Player::draw() const {
	DrawCircle(x, y, Radius, Color);
}