# C++DxLib講座資料

## はじめに

本資料は、やぎりが作成した、C++初学者向け資料です。  
C++とDXライブラリで実際にシューティングゲームを作り、「C++の機能(クラス, vector, 継承)をゲームを製作に実際どう使うか」を理解することが目的になっています。  

## 開発環境

開発環境はWindows, Visual Studio 2017、DXライブラリのバージョンはDxLib 3.18eを想定しています。  
 
## 謝辞

本資料の一部は、[いかろちゃんのサークル用C++講座資料](https://turarasoft.com/main/ccs/index.html)を参考に作りました。ありがとうございました。  

## 演習問題について

DxLib.hをインクルードしているプログラムはDXライブラリを使ったアプリケーションを、そうでないプログラムはコンソールアプリケーション(文字だけ出てくる黒画面のやつ)で解くことを想定しています。  
演習問題（コンソール)の解答は、「vol_12_演習問題(コンソール)」の解答の解答に書いてあります。  
演習問題(DxLib)の解答例はAnsweExampleフォルダ内に入っています。  

## ファイルについて

* AnsweExampleフォルダ  
各回の演習問題(DxLib)の解答例です。

* SampleGame.exe  
前半課題、最終課題ではこれを作ります。

* DxLibTemplate2017.zip  
DxLibの初期設定済みのVisual Studio2017プロジェクトです．これを改造して演習問題を解くことをおすすめします．

## 今回やること

今回はコンソールの問題を解く際の豆知識や，本資料でよく使うDxLibの関数，機能についての解説を行います。

## \#if~\#endif

\#ifと\#endifで囲んだ部分は、\#ifの右に来る条件式がtrue(=0以外)の場合はコンパイルされ、false(=0)の場合はコンパイルされない。  
コメントアウトのように使うことができる。  
講座中の演習問題（コンソール)では、一問解くたびに新しいプロジェクトを作るのは手間がかかるので、\#if-\#endifを使って一つのプロジェクト内に複数の演習問題の解答のコードを作っていくとよい。  

```cpp
#if 1

#include <iostream>

int main(){
    std::cout << "aaa" << std::endl;
    return 0;
}

#endif

#if 0

#include <iostream>

int main(){
    std::cout << "bbb" << std::endl;
    return 0;
}

#endif

#if 0

#include <iostream>

int main(){
    std::cout << "ccc" << std::endl;
    return 0;
}

#endif
```


## DXライブラリコード例

この講座では演習にDxLibを使う。以下ではDxLibの基本的なコードや、私が作ったDxLibのひな形のコードについて説明している。  
画面中央に円を描画するだけの基本的なコード。  


```cpp
#include <DxLib.h>
#include <iostream>


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
    SetOutApplicationLogValidFlag( FALSE ) ;//Log.txtを生成しないように設定
    ChangeWindowMode( TRUE );//非全画面にセット
    SetGraphMode( 640 , 480 , 32 );//画面サイズ指定
    if(DxLib_Init() == 1){return -1;}//初期化に失敗時にエラーを吐かせて終了

    //
    //ここで敵やプレイヤーのオブジェクトの実体を作る
    //

    while( ProcessMessage()==0 )
    {
        ClearDrawScreen();//裏画面消す
        SetDrawScreen( DX_SCREEN_BACK ) ;//描画先を裏画面に

        //
        //　ここに敵やプレイヤーを更新、描画するコードを書く
        //

        DrawCircle(400, 320, 100, GetColor(255, 255, 255), 1);

        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}
```



## DXライブラリコード例　その２

下の例では、キーの状態を記録する配列とそれを更新する関数を用意して、フォントを指定して文字を描画（DrawFormatStringToHandle）している。  
変数にexternをつけて宣言することで複数のcppやヘッダーからその変数にアクセスできるようになる。

> MyGlobal.h

```cpp
#pragma once
#include "DxLib.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern int fontHandle;
extern int mouseX , mouseY;//マウス座標

//キー取得マウス付き
extern char buf[256];
extern int keyState[256];

//キー入力状態を更新する関数
void keyUpdate();
```


> MyGlobal.cpp

```cpp
#pragma once

#include "MyGlobal.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int fontHandle;//フォント読み込み用変数
int mouseX=0 , mouseY=0;//マウス座標

//キー取得用の配列
char buf[256] = {0};
int keyState[256] = {0};

//キー入力状態を更新する関数
void keyUpdate()
{
    GetHitKeyStateAll(buf);
    for(int i = 0; i< 256; i++)
    {
        if(buf[i] == 1) keyState[i]++;
        else keyState[i] = 0;
    }
}
```


> main.cpp

```cpp
#include <DxLib.h>
#include <iostream>

#include "MyGlobal.h"


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
    SetOutApplicationLogValidFlag( FALSE ) ;//Log.txtを生成しないように設定
    ChangeWindowMode( TRUE );//非全画面にセット
    SetGraphMode( SCREEN_WIDTH , SCREEN_HEIGHT , 32 );//画面サイズ指定
    if(DxLib_Init() == 1){return -1;}//初期化に失敗時にエラーを吐かせて終了
    

    fontHandle = CreateFontToHandle( "Segoe UI" , 20 , 5 ,DX_FONTTYPE_ANTIALIASING_4X4) ;//フォントを読み込み

    //
    //ここで敵やプレイヤーのオブジェクトの実体を作る
    //

    while( ProcessMessage()==0 )
    {
        ClearDrawScreen();//裏画面消す
        SetDrawScreen( DX_SCREEN_BACK ) ;//描画先を裏画面に

        GetMousePoint( &mouseX, &mouseY ); //マウス座標更新
        keyUpdate();//(自作関数)キー更新
        
        //説明用・文字を描画：keyState配列（自作）には、各キーが何フレーム押され続けているかが入っている
        DrawFormatStringToHandle(320, 320, GetColor(255, 255, 255), fontHandle , "Z KEY %d", keyState[KEY_INPUT_Z]) ;

        //
        //　ここに敵やプレイヤーのupdate,drawを書く
        //

        //左上に文字（マウスの座標）を描画
        DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle , "MX:%3d MY:%3d", mouseX,mouseY) ;

        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}
```



## キーが何フレーム押されているかを取得

GetHitKeyStateAll関数は引数にとった配列に各キーの状態（押されていれば1, そうでなければ0)を入れる。  
下のような関数を自分で作れば、どのキーが何フレーム押されているかを配列に入れることができる。(この関数は毎フレーム呼ばなければいけない)  

```cpp
//キー取得用の配列
char buf[256] = {0};
int keyState[256] = {0};

//キー入力状態を更新する関数
void keyUpdate()
{
    GetHitKeyStateAll(buf);
    for(int i = 0; i< 256; i++)
    {
        if(buf[i] == 1) keyState[i]++;
        else keyState[i] = 0;
    }
}
```

## フォントを指定して文字を描画

DrawFormatStringToHandle関数を使えば、座標、色、フォントを指定して文字を描画できる。printfと同じように%dなどが使える。  

```cpp
DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), fontHandle , "MX:%3d MY:%3d", mouseX,mouseY) ;
```

## 演習問題

1. double型の変数x, yを用意し、DrawCircleを用いてx,yに半径20pxの赤い円を描画せよ。  

1. 矢印キーを押したとき上記で描画した円が動くようにせよ。（xやyに数字を足せばよい）  

1. Zキーを押したフレームにx座標にGetRand(100)を加算せよ。  
ヒント：GetRandはDXライブラリの関数で，乱数を返す。GetRand(100)で0~100の数のうちどれかが返ってくる。（0~99でないことに注意！）