#include <iostream>
#include <vector>

#include "DxLib.h"

#include "MyGlobal.h"
#include "Enemy.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//画面サイズ指定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に


	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	std::vector<Enemy> vec;

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

		// Zキーが押されたらランダムな座標に敵を生成
		if (keyState[KEY_INPUT_Z] == 1) {
			vec.emplace_back(Enemy(GetRand(SCREEN_WIDTH), GetRand(SCREEN_HEIGHT))); // 敵をインスタンス化
		}

		// 画面外の敵を削除
		auto iter = vec.begin();
		while (iter != vec.end()) {
			if (iter->x < 0 || iter->x > SCREEN_WIDTH || iter->y < 0 || iter->y > SCREEN_HEIGHT) { //画面外に出ているか確認
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

		DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle, "Zキーで敵を生成 敵の数:%d", vec.size());

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}

