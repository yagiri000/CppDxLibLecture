#include "DxLib.h"
#include <algorithm>
#include "Enemy.h"

void Main()
{
	std::vector<Enemy> vec;

	const Font font(18);

	while (System::Update())
	{
		// Zキーが押されたらランダムな座標に敵を生成
		if (Input::KeyZ.pressed) {
			// RandomVec2(double xMax, double yMax) : 
			// (0 < x < xMax, 0 < y < yMax) の2次元ベクトルを返す

			vec.emplace_back(Enemy(RandomVec2(Window::Width(), Window::Height() / 2.0))); // 敵をインスタンス化
		}

		auto rmvIter = std::remove_if(vec.begin(), vec.end(), [](const Enemy& i) {
			return i.x < 0 || i.x > Window::Height() || i.y < 0 || i.y > Window::Height();
		});

		vec.erase(rmvIter, vec.end());

		for (auto i = vec.begin(); i < vec.end(); i++) {
			i->update();
		}
		for (auto i = vec.begin(); i < vec.end(); i++) {
			i->draw();
		}


		// 敵の数を描画
		font(L"敵の数:", vec.size()).draw();
	}
}
