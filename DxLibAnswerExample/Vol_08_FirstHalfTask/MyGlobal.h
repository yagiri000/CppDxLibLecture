#pragma once
#include "DxLib.h"

extern int mouseX, mouseY;//マウス座標

//キー取得用配列
extern char buf[256];
extern int keyState[256];

extern const double PI2;

//キー入力状態を更新する関数
void keyUpdate();

// 点(x, y)が四角形(左上:(leftTopX, leftTopY), 右下(rightBottomX, rightBottomY))の中にあるか返す
bool checkHitPointRect(double x, double y, double leftTopX, double leftTopY, double rightBottomX, double rightBottomY);

// (startX, startY) - (endX, endY)の単位ベクトルを求め，結果をresultX, resultYに入れる
void normalize(double startX, double startY, double endX, double endY, double *resultX, double *resultY);

// 長さradiusでランダムな方向のベクトルを(x, y)計算し，ポインタを介して値を入れる
void randomInCircle(double radius, double * x, double * y);

// 2円が接触しているか返す関数
// 2円とは，円A(中心:(ax, ay),半径:ar) と円B(中心:(bx, by),半径:br)
bool checkHitCircles(double ax, double ay, double ar, double bx, double by, double br);
