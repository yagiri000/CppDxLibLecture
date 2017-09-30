#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::update() {
	// A, S, D�L�[�������ƁA���@��ǂ��G�A���̏�ŉ�]����G�A�܂������i�ޓG�𐶐�
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

	font(L"ASD�œG�𐶐�").draw(Vec2(10.0, 30.0 * 3.0));
	font(L"Z�ŃV���b�g").draw(Vec2(10.0, 30.0 * 4.0));
}

void GameManager::load() {
	font = Font(15);
}

GameManager gameManager;