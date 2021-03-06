#pragma once
#include <vector>
#include <memory>
#include "IEnemy.h"

//敵全体を管理するクラス
class EnemyManager {
public:
	std::vector<std::shared_ptr<IEnemy>> enemies;
	EnemyManager();
	void add(const std::shared_ptr<IEnemy>& ptr);
	void update();
	void draw() const;
};

