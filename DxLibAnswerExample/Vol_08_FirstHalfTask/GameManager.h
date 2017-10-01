#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Player.h"
#include "PlayerBulletManager.h"
#include "EnemyManager.h"
#include "EnemyBulletManager.h"
#include "EffectManager.h"
#include "ScoreManager.h"

class GameManager{
public:
	Player player;
	PlayerBulletManager pBulletManager;
	EnemyManager enemyManager;
	EnemyBulletManager eBulletManager;
	EffectManager effectManager;
	ScoreManager scoreManager;
	int fontHandle;

	GameManager();
	void update();
	void draw() const;
	void load();
};

extern GameManager gameManager;