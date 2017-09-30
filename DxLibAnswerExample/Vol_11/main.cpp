#include "DxLib.h"
#include <memory>
#include <algorithm>
#include "Enemy.h"

void Main()
{
	std::vector<std::shared_ptr<IEnemy>> vec;
	const Font font(18);

	while (System::Update())
	{
		// Z, X, Cキーが押されたらランダムな座標に敵を生成
		if (keyState[KEY_INPUT_Z] == 1) {
			vec.emplace_back(std::make_shared<EnemySinMove>(GetRand(640), GetRand(480)));
		}
		if (keyState[KEY_INPUT_X] == 1) {
			vec.emplace_back(std::make_shared<EnemyRotation>(GetRand(640), GetRand(480)));
		}
		if (keyState[KEY_INPUT_C] == 1) {
			vec.emplace_back(std::make_shared<EnemyStraight>(GetRand(640), GetRand(480)));
		}
		
		// 画面外の敵を削除
		auto rmvIter = std::remove_if(vec.begin(), vec.end(), [](const std::shared_ptr<IEnemy>& enemy) {
			return !Circle(enemy->pos, enemy->Radius).intersects(Rect(Window::Size()));
		});

		vec.erase(rmvIter, vec.end());

		for (const auto& enemy : vec) {
			enemy->update();
		}

		for (const auto& enemy : vec) {
			enemy->draw();
		}

		// 敵の数を描画
		font(L"敵の数:", vec.size()).draw();
	}
}
