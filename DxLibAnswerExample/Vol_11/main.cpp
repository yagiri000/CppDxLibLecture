# include <Siv3D.hpp>
# include <memory>
# include <algorithm>
# include "Enemy.h"

void Main()
{
	std::vector<std::shared_ptr<IEnemy>> vec;
	const Font font(18);

	while (System::Update())
	{
		// Z, X, Cキーが押されたらランダムな座標に敵を生成
		if (Input::KeyZ.clicked) {
			vec.emplace_back(std::make_shared<EnemySinMove>(RandomVec2(Window::Width(), Window::Height() / 2.0)));
		}
		if (Input::KeyX.clicked) {
			vec.emplace_back(std::make_shared<EnemyRotation>(RandomVec2(Window::Width(), Window::Height() / 2.0)));
		}
		if (Input::KeyC.clicked) {
			vec.emplace_back(std::make_shared<EnemyStraight>(RandomVec2(Window::Width(), Window::Height() / 2.0)));
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
