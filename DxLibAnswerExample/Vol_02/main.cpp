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

																					 //
																					 //ここで敵やプレイヤーのオブジェクトの実体を作る
																					 //

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

					//説明用・文字を描画：keyState配列（自作）には、各キーが何フレーム押され続けているかが入っている
		DrawFormatStringToHandle(320, 320, GetColor(255, 255, 255), fontHandle, "Z KEY %d", keyState[KEY_INPUT_Z]);

		//
		//　ここに敵やプレイヤーのupdate,drawを書く
		//

		//左上に文字（マウスの座標）を描画
		DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle, "MX:%3d MY:%3d", mouseX, mouseY);

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}