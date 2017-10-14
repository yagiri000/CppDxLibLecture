#include <iostream>
#include <string>
#include "DxLib.h"
#include "MyGlobal.h"

// string型を使う例

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//画面サイズ指定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に


	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	std::string text = "やきそば！";

	while (ProcessMessage() == 0) {
		ClearDrawScreen();//裏画面消す

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

		DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle, "Z, Xで文字追加");

		// キー入力で文字追加
		if (keyState[KEY_INPUT_Z] == 1) {
			text += "そば！";
		}
		if (keyState[KEY_INPUT_X] == 1) {
			text += "うどん！";
		}

		// 文字列を表示
		DrawFormatStringToHandle(20, 60, GetColor(255, 255, 255), fontHandle, text.c_str());

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}