#include "DxLib.h"
#include "Enemy.h"

void Main()
{
	std::vector<IEnemy*> vec;
	const Font font(18);

	while (System::Update())
	{
		// Z, X, Cキーが押されたらランダムな座標に敵を生成
		if (keyState[KEY_INPUT_Z] == 1) {
			vec.emplace_back(new EnemySinMove(RandomVec2(Window::Width(), Window::Height() / 2.0)));
		}
		if (Input::KeyX.clicked) {
			vec.emplace_back(new EnemyRotation(RandomVec2(Window::Width(), Window::Height() / 2.0)));
		}
		if (Input::KeyC.clicked) {
			vec.emplace_back(new EnemyStraight(RandomVec2(Window::Width(), Window::Height() / 2.0)));
		}

		// 画面外の敵を削除
		auto it = vec.begin();
		while (it != vec.end()) {
			// 画面外に出ているか確認
			// 敵の円と画面の長方形との当たり判定を取り、その否定を条件にすることで画面外に出ているか確認している
			if (!Circle((*it)->pos, (*it)->Radius).intersects(Rect(Window::Size()))) { 
				// メモリ解放
				delete (*it);
				it = vec.erase(it);
			}
			else {
				it++;
			}
		}

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
