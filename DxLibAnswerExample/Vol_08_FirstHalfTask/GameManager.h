#pragma once
#include "Player.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
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
	Font font;

	GameManager();
	void update();
	void draw() const;
	void load();
};

extern GameManager gameManager;