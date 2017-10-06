#include "DxLib.h"
#include "GameManager.h"
#include "MyGlobal.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//画面サイズ指定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に


	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す

		GetMousePoint(&mouseX, &mouseY); //マウス座標更新
		keyUpdate();//(自作関数)キー更新

		// Z, X, Cキーを押すと、自機を追う敵、その場で回転する敵、まっすぐ進む敵を生成
		if (keyState[KEY_INPUT_Z] == 1) {
			gameManager.enemyManager.add(Enemy(GetRand(SCREEN_WIDTH), GetRand(SCREEN_HEIGHT), Enemy::Stalker));
		}
		if (keyState[KEY_INPUT_X] == 1) {
			gameManager.enemyManager.add(Enemy(GetRand(SCREEN_WIDTH), GetRand(SCREEN_HEIGHT), Enemy::Rotation));
		}
		if (keyState[KEY_INPUT_C] == 1) {
			gameManager.enemyManager.add(Enemy(GetRand(SCREEN_WIDTH), GetRand(SCREEN_HEIGHT), Enemy::Straight));
		}

		gameManager.update();
		gameManager.draw();

		DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle, "Z, X Cで敵生成 敵の数:%d", gameManager.enemyManager.getEnemyNum());

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}