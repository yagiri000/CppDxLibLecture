#include "DxLib.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "MyGlobal.h"

#include <iostream>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(640, 480, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	EnemyManager enemyManager; // EnemyManagerのインスタンスを生成

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

		// Zキーが押されたら敵を生成
		if (keyState[KEY_INPUT_Z] == 1) {
			enemyManager.add(Enemy(GetRand(640), GetRand(480)));
		}

		enemyManager.update();
		enemyManager.draw();

		DrawFormatStringToHandle(20, 40, 0xFFFFFF, fontHandle, "敵の数:%3d", enemyManager.enemies.size());

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}