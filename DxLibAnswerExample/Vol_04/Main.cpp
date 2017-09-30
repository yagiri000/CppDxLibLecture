# include <Siv3D.hpp>
# include "Player.h"
# include "Enemy.h"

void Main()
{
	Player player; // プレイヤーをインスタンス化
	Enemy enemy(Vec2(320.0, 100.0)); // 敵をインスタンス化

	// プレイヤーへのポインタを取得
	enemy.setPlayerPtr(&player);

	while (System::Update())
	{
		player.update();
		enemy.update();

		player.draw();
		enemy.draw();
	}
}
