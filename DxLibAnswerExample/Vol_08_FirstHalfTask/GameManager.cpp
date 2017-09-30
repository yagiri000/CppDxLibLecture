#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::update() {
	// A, S, Dキーを押すと、自機を追う敵、その場で回転する敵、まっすぐ進む敵を生成
	if (Input::KeyA.clicked) {
		gameManager.enemyManager.add(Enemy(RandomVec2(Window::Width(), Window::Height() / 2.0), Enemy::Stalker));
	}
	if (Input::KeyS.clicked) {
		gameManager.enemyManager.add(Enemy(RandomVec2(Window::Width(), Window::Height() / 2.0), Enemy::Stop));
	}
	if (Input::KeyD.clicked) {
		gameManager.enemyManager.add(Enemy(RandomVec2(Window::Width(), Window::Height() / 2.0), Enemy::Rotation));
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

	font(L"ASDで敵を生成").draw(Vec2(10.0, 30.0 * 3.0));
	font(L"Zでショット").draw(Vec2(10.0, 30.0 * 4.0));
}

void GameManager::load() {
	font = Font(15);
}

GameManager gameManager;