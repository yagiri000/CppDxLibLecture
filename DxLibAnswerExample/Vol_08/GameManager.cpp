#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::update()
{
	player.update();
	enemyManager.update();
}

void GameManager::draw()
{
	player.draw();
	enemyManager.draw();
}


GameManager gameManager;