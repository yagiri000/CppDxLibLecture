#pragma once
#include "Player.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Effect.h"
#include "ScoreMgr.h"

class GameManager {
public:
	Player player;
	PlayerBulletManager playerBulletManager;
	EnemyManager enemyManager;
	EnemyBulletManager enemyBulletManager;
	EffectManager effectManager;
	ScoreManager scoreManager;
	int fontHandle;

	GameManager();
	void update();
	void draw() const;
	void load();
};

extern GameManager gameManager;