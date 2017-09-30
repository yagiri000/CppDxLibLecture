#include "DxLib.h"
#include "Enemy.h"
#include "EnemyManager.h"

void Main()
{
	EnemyManager enemyManager; // EnemyManagerのインスタンスを生成

	while (System::Update())
	{
		// Zキーが押されたら敵を生成
		if (keyState[KEY_INPUT_Z] == 1) {
			enemyManager.add(Enemy(Vec2(Random(0.0, 640.0), Random(0.0, 240.0))));
		}

		enemyManager.update();
		enemyManager.draw();
	}
}
