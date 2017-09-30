#pragma once
#include "Player.h"
#include "EnemyManager.h"

class GameManager
{
public:
	GameManager();
	Player player;
	EnemyManager enemyManager;
	void update();
	void draw();
};

extern GameManager gameManager;