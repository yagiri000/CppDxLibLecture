#include "DxLib.h"
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

		// 画面外の敵を削除
		auto iter = vec.begin();
		while (iter != vec.end()) {
			if (iter->x < 0 || iter->x > Window::Height() || iter->y < 0 || iter->y > Window::Height()) { //画面外に出ているか確認
				iter = vec.erase(iter);
			}
			else {
				iter++;
			}
		}

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
