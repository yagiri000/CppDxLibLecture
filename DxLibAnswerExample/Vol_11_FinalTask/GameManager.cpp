#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::update() {
	// A, S, DƒL[‚ğ‰Ÿ‚·‚ÆA©‹@‚ğ’Ç‚¤“GA‚»‚Ìê‚Å‰ñ“]‚·‚é“GA‚Ü‚Á‚·‚®i‚Ş“G‚ğ¶¬
	if (Input::KeyA.clicked) {
		gameManager.enemyManager.add(std::make_shared<EnemyStalker>(RandomVec2(Window::Width(), Window::Height() / 2.0)));
	}
	if (Input::KeyS.clicked) {
		gameManager.enemyManager.add(std::make_shared<EnemyStop>(RandomVec2(Window::Width(), Window::Height() / 2.0)));
	}
	if (Input::KeyD.clicked) {
		gameManager.enemyManager.add(std::make_shared<EnemyRotation>(RandomVec2(Window::Width(), Window::Height() / 2.0)));
	}

	player.update();
	enemyManager.update();
	playerBulletManager.update();
	enemyBulletManager.update();
	effectManager.update();
	scoreManager.update();
}

void GameManager::draw() const {
	player.draw();
	enemyManager.draw();
	playerBulletManager.draw();
	enemyBulletManager.draw();
	effectManager.draw();
	scoreManager.draw();

	font(L"ASD‚Å“G‚ğ¶¬").draw(Vec2(10.0, 30.0 * 3.0));
	font(L"Z‚ÅƒVƒ‡ƒbƒg").draw(Vec2(10.0, 30.0 * 4.0));
}

void GameManager::load() {
	font = Font(15);
}

GameManager gameManager;