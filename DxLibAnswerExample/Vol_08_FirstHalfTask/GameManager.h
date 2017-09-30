#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "EnemyManager.h"
#include "EnemyBullet.h"
#include "Effect.h"
#include "ScoreMgr.h"

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