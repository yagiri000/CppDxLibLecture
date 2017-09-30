# include <Siv3D.hpp>
# include "Enemy.h"
# include "EnemyManager.h"

void Main()
{
	EnemyManager enemyManager; // EnemyManagerのインスタンスを生成

	while (System::Update())
	{
		// Zキーが押されたら敵を生成
		if (Input::KeyZ.clicked) {
			enemyManager.add(Enemy(Vec2(Random(0.0, 640.0), Random(0.0, 240.0))));
		}

		enemyManager.update();
		enemyManager.draw();
	}
}
