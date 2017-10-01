#include <algorithm>
#include <memory>
#include "DxLib.h"
#include "GameManager.h"
#include "MyGlobal.h"
#include "IEnemy.h"
#include "WhiteCircleEffect.h"

const size_t IEnemy::EffectNum = 25;
const double IEnemy::EffectGenerateRange = 64.0;


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
			gameManager.effectManager.add(std::make_shared<WhiteCircleEffect>(bullet->x, bullet->y));
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
			gameManager.effectManager.add(std::make_shared<WhiteCircleEffect>(x + ix, y + iy));
		}
		isDead = true;
	}
}

