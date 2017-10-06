#include <iostream>
#include "DxLib.h"

#include "MyGlobal.h"

class Player {
public:
	double x, y, speed;

	Player() {
		x = 320.0;
		y = 360.0;
		speed = 5.0;
	}
	void update() {
		// 上下左右キーで移動
		if (keyState[KEY_INPUT_LEFT] > 0) {
			x -= speed;
		}
		if (keyState[KEY_INPUT_RIGHT] > 0) {
			x += speed;
		}
		if (keyState[KEY_INPUT_UP] > 0) {
			y -= speed;
		}
		if (keyState[KEY_INPUT_DOWN] > 0) {
			y += speed;
		}
	}

	//自機（円）を描画
	void draw() {
		DrawCircle(x, y, 30.0, GetColor(0, 0, 255));
	}
};


class Enemy {
public:
	double x, y;

	Enemy(double _x, double _y) {
		x = _x;
		y = _y;
	}

	void update() {
		//下方向に移動
		y += 1.0;
	}

	//エネミー（円）を描画
	void draw() {
		DrawCircle(x, y, 30.0, GetColor(255, 0, 0));
	}
};



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
	ChangeWindowMode(TRUE);//非全画面にセット
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);//画面サイズ指定
	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に


	fontHandle = CreateFontToHandle("Segoe UI", 20, 5, DX_FONTTYPE_ANTIALIASING_4X4);//フォントを読み込み

	Player player;
	Enemy enemy(320.0, 120.0);

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す

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