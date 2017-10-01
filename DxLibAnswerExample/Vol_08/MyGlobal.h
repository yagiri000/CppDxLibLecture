#pragma once
#include "DxLib.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern int fontHandle;
extern int mouseX, mouseY;//マウス座標

 //キー取得用配列
extern char buf[256];
extern int keyState[256];

//キー入力状態を更新する関数
void keyUpdate();

// 点(x, y)が四角形(左上:(leftTopX, leftTopY), 右下(rightBottomX, rightBottomY))の中にあるか返す
bool checkHitPointRect(double x, double y, double leftTopX, double leftTopY, double rightBottomX, double rightBottomY);

// (startX, startY) - (endX, endY)の単位ベクトルを求め，結果をresultX, resultYに入れる
void normalize(double startX, double startY, double endX, double endY, double *resultX, double *resultY);