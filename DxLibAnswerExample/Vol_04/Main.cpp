#include <iostream>
#include "DxLib.h"

# include "Player.h"
# include "Enemy.h"
#include "MyGlobal.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(640, 480, 32);//画面サイズ指定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了


	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	Player player; // プレイヤーをインスタンス化
	Enemy enemy(320.0, 120.0); // 敵をインスタンス化

	// プレイヤーへのポインタを取得
	enemy.setPlayerPtr(&player);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

		player.update();
		enemy.update();

		player.draw();
		enemy.draw();

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}