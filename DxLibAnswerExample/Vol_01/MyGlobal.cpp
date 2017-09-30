#pragma once

#include "myglobal.h"

int fontHandle;//フォント読み込み用変数
int mouseX = 0, mouseY = 0;//マウス座標

						   //キー取得用の配列
char buf[256] = { 0 };
int keyState[256] = { 0 };

//キー入力状態を更新する関数
void keyUpdate()
{
	GetHitKeyStateAll(buf);
	for (int i = 0; i< 256; i++)
	{
		if (buf[i] == 1) keyState[i]++;
		else keyState[i] = 0;
	}
}