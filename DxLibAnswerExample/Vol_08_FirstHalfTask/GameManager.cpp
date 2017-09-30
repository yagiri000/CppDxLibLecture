#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::update() {
	// A, S, DƒL[‚ğ‰Ÿ‚·‚ÆA©‹@‚ğ’Ç‚¤“GA‚»‚Ìê‚Å‰ñ“]‚·‚é“GA‚Ü‚Á‚·‚®i‚Ş“G‚ğ¶¬
	if (Input::KeyA.clicked) {
		gameManager.enemyManager.add(Enemy(GetRand(640), GetRand(480), Enemy::Stalker));
	}
	if (Input::KeyS.clicked) {
		gameManager.enemyManager.add(Enemy(GetRand(640), GetRand(480), Enemy::Stop));
	}
	if (Input::KeyD.clicked) {
		gameManager.enemyManager.add(Enemy(GetRand(640), GetRand(480), Enemy::Rotation));
	}

	player.update();
	enemyManager.update();
	pBulletManager.update();
	eBulletManager.update();
	effectManager.update();
	scoreManager.update();
}

void GameManager::draw() const {
	player.draw();
	enemyManager.draw();
	pBulletManager.draw();
	eBulletManager.draw();
	effectManager.draw();
	scoreManager.draw();

	font(L"ASD‚Å“G‚ğ¶¬").draw(Vec2(10.0, 30.0 * 3.0));
	font(L"Z‚ÅƒVƒ‡ƒbƒg").draw(Vec2(10.0, 30.0 * 4.0));
}

void GameManager::load() {
	font = Font(15);
}

GameManager gameManager;