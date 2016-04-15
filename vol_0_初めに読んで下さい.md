#C++講座資料 vol_0  

本資料は、C++初学者向けの資料です。DXライブラリとC++で実際にプログラムを組んで、C++とポリモーフィズムを理解することを目的としています。  

> 作成にあたって、いかろちゃん先輩の資料、[いかろちゃんのC++講座(仮)](http://turarasoft.com/main/kouza/index.html)を一部参考にしました。ありがとうございました。

今回は、DxLibの基本的な使い方などについて説明します。  


##\#if~\#endif
\#ifと\#endifで囲んだ部分は、\#ifの右に来る条件式がtrue(=0以外)の場合はコンパイルされ、false(=0)の場合はコンパイルされない。  
コメントアウトのように使うことができる。  
講座中の演習問題（Dxlibを使わないもの)では、一問解くたびに新しいプロジェクトを作るのは手間がかかるので、\#if-\#endifを使って一つのプロジェクト内に複数の演習問題の解答のコードを作っていくとよい。  

```c++
#if 1

#include <iostream>

int main(void){
	std::cout << "aaa" << std::endl;
	return 0;
}

#endif

#if 0

#include <iostream>

int main(void){
	std::cout << "bbb" << std::endl;
	return 0;
}

#endif

#if 0

#include <iostream>

int main(void){
	std::cout << "ccc" << std::endl;
	return 0;
}

#endif
```


##DXライブラリ　コード例
この講座では演習にDxLibを使う。以下ではDxLibの基本的なコードや、私が作ったDxLibのひな形のコードについて説明している。  
（DxLibのひな形は、wikiに上がっています）    

画面中央に円を描画するだけの基本的なコード。


```c++
#include <DxLib.h>
#include <iostream>


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
    ChangeWindowMode( TRUE );//非全画面にセット
    SetGraphMode( 800 , 600 , 32 );//画面サイズ指定
    SetOutApplicationLogValidFlag( FALSE ) ;//Log.txtを生成しないように設定
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

		DrawCircle(400, 300, 100, GetColor(255, 255, 255), 1);

        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}
```



##DXライブラリ　コード例　その２
下の例では、キーの状態を記録する配列とそれを更新する関数を用意して、  
フォントを指定して文字を描画（DrawFormatStringToHandle）している。  
変数にexternをつけて宣言することで複数のcppやヘッダーからその変数にアクセスできるようになる。

>myglobal.h

```c++
#pragma once
#include "DxLib.h"

extern int FontHandle;
extern int mousex , mousey;//マウス座標

//キー取得マウス付き
extern char buf[256];
extern int keystate[256];

//キー入力状態を更新する関数
void keyupdate();
```


>myglobal.cpp

```c++
#pragma once

#include "myglobal.h"

int FontHandle;//フォント読み込み用変数
int mousex=0 , mousey=0;//マウス座標

//キー取得用の配列
char buf[256] = {0};
int keystate[256] = {0};

//キー入力状態を更新する関数
void keyupdate()
{
	GetHitKeyStateAll(buf);
	for(int i = 0; i< 256; i++)
	{
		if(buf[i] == 1) keystate[i]++;
		else keystate[i] = 0;
	}
}
```


>main.cpp

```c++
#include <DxLib.h>
#include <iostream>

#include "myglobal.h"


int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	ChangeWindowMode( TRUE );//非全画面にセット
	SetGraphMode( 800 , 600 , 32 );//画面サイズ指定
	SetOutApplicationLogValidFlag( FALSE ) ;//Log.txtを生成しないように設定
	if(DxLib_Init() == 1){return -1;}//初期化に失敗時にエラーを吐かせて終了
	

	FontHandle = CreateFontToHandle( "Segoe UI" , 20 , 5 ,DX_FONTTYPE_ANTIALIASING_4X4) ;//フォントを読み込み

	//
	//ここで敵やプレイヤーのオブジェクトの実体を作る
	//

	while( ProcessMessage()==0 )
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen( DX_SCREEN_BACK ) ;//描画先を裏画面に

		GetMousePoint( &mousex, &mousey ); //マウス座標更新
		keyupdate();//(自作関数)キー更新
		
		//説明用・文字を描画：keystate配列（自作）には、各キーが何フレーム押され続けているかが入っている
		DrawFormatStringToHandle(300, 300, GetColor(255, 255, 255), FontHandle , "Z KEY %d", keystate[KEY_INPUT_Z]) ;

		//
		//　ここに敵やプレイヤーのupdate,drawを書く
		//

		//左上に文字（マウスの座標）を描画
		DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), FontHandle , "MX:%3d MY:%3d", mousex,mousey) ;

		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();
	return 0;
}
```



##キーが何フレーム押されているかを取得
GetHitKeyStateAll関数は引数にとった配列に各キーの状態（押されていれば1, そうでなければ0)を入れる。  
下のような関数を自分で作れば、どのキーが何フレーム押されているかを配列に入れることができる。(この関数は毎フレーム呼ばなければいけない)

```c++
//キー取得用の配列
char buf[256] = {0};
int keystate[256] = {0};

//キー入力状態を更新する関数
void keyupdate()
{
	GetHitKeyStateAll(buf);
	for(int i = 0; i< 256; i++)
	{
		if(buf[i] == 1) keystate[i]++;
		else keystate[i] = 0;
	}
}
```

##フォントを指定して文字を描画
DrawFormatStringToHandle関数を使えば、座標、色、フォントを指定して文字を描画できる。printfと同じように%dなどが使える。

```c++
DrawFormatStringToHandle(20, 20, GetColor(255, 255, 255), FontHandle , "MX:%3d MY:%3d", mousex,mousey) ;
```

##演習問題
1. double型の変数x, yを用意し、DrawCircleを用いてx,yに半径20pxの赤い円を描画せよ。

1. 矢印キーを押したとき上記で描画した円が動くようにせよ。（xとかyに数字を足せばよい）

1. Zキーを押したフレームにx座標にGetRand(100)を加算せよ。  
ヒント：GetRandはDXライブラリについている乱数を返す関数。GetRand(100)で0~100の数のうちどれかが返ってくる。（0~99でないことに注意！）