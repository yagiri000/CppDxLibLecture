#include <iostream>
#include "DxLib.h"

#include "MyGlobal.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(640, 480, 32);//画面サイズ指定
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了


	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	double x = 320.0;
	double y = 240.0;
	const double SPEED = 5.0;

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

		// 上下左右キーで移動
		if (keyState[KEY_INPUT_LEFT] > 0) {
			x -= SPEED;
		}
		if (keyState[KEY_INPUT_RIGHT] > 0) {
			x += SPEED;
		}
		if (keyState[KEY_INPUT_UP] > 0) {
			y -= SPEED;
		}
		if (keyState[KEY_INPUT_DOWN] > 0) {
			y += SPEED;
		}

		// Zキーを押したフレームでランダムに移動
		if (keyState[KEY_INPUT_Z] == 1) {
			x += GetRand(100);
		}

		// x, yに赤の円を描画
		DrawCircle(x, y, 20, GetColor(255, 0, 0));

		//左上に文字（マウスの座標）を描画
		DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle, "X:%.0f Y:%.0f", x, y);

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}