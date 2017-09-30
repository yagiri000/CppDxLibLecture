#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::update() {
	// A, S, Dキーを押すと、自機を追う敵、その場で回転する敵、まっすぐ進む敵を生成
	if (Input::KeyA.clicked) {
		gameManager.enemyManager.add(std::make_shared<EnemyStalker>(GetRand(640), GetRand(480)));
	}
	if (Input::KeyS.clicked) {
		gameManager.enemyManager.add(std::make_shared<EnemyStop>(GetRand(640), GetRand(480)));
	}
	if (Input::KeyD.clicked) {
		gameManager.enemyManager.add(std::make_shared<EnemyRotation>(GetRand(640), GetRand(480)));
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

	DrawFormatStringToHandle(10, 30 * 3, GetColor(255, 255, 255), fontHandle, "A, S, Dで敵を生成");
	DrawFormatStringToHandle(10, 30 * 4, GetColor(255, 255, 255), fontHandle, "Zでショット");
}

void GameManager::load() {
	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み
}

GameManager gameManager;