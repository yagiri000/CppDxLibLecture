# C++DxLib講座資料

今回はC++でのHello World、クラスの基本的な使い方について学ぶ。  
演習では、実際にDxLibを用いてPlayer,Enemyを生成し、動かす。  

## Hello World!

C++流のHello World!
C++ではstd::coutが用意されており、それを使って出力ができる。  
std::　とは、「stdという名前空間にある」という意味。

```cpp
#include <iostream>

int main(){

    std::cout << "Hello World!!" << std::endl;
    
    return 0;
}
```

## いろいろ出力

Cのprintf関数では%dや%sなどを使って型を指定する必要があったが、std::coutでは型を指定しなくても自動的に型を判定・表示してくれる。  

```cpp
#include <iostream>

int main(){

    int a = 12;
    double b = 3.14;
    char str[100] = "abcde";
    
    std::cout << a << " " << b << " " << str << std::endl;
    
    return 0;
}
```

## 入力

std::cinを使うと入力されたデータを変数に入れられる。  

```cpp
#include <iostream>

int main(){
 
    int input;
    std::cout << "年齢を入力してください" << std::endl;
    std::cin >> input;//inputに入力された数値を代入
  
    std::cout << "あなたは"<< input << "歳なんですね。" << std::endl;    
 
    return 0;
}
```

## クラスの基本的な書き方

クラスは以下のように定義でき、インスタンス(実体)化して使う。  
クラスの要素には```.```（コンマ）を使ってアクセスできる。  
クラスは変数を要素に持つことができ、メンバ変数という。  

```cpp
#include <iostream>

class MyClass{
public:
	int a;
	int b;
};

int main(){

	MyClass obj; // インスタンス化
	obj.a = 10;
	obj.b = 20;
	std::cout << obj.a << "," << obj.b << std::endl;
	
	return 0;
}
```

二次元上の座標や、2次元ベクトルを表すクラス、Vector2を作った。  
クラスの要素には```.```（コンマ）を使ってアクセスできる。  
クラスは関数を要素に持つことができ、メンバ関数という。（下の例ではsetData関数がメンバ関数）  

```cpp
#include <iostream>

class Vector2{
public:
	int x;
	int y;
	void setData(int _x, int _y){
		x = _x;
		y = _y;
	}
};

int main(){

	Vector2 obj;
	obj.setData(13, 29);
	std::cout << obj.x << " " << obj.y << std::endl;
	
	return 0;
}
```

## コンストラクタ

さっきの例ではVector2クラスを作った後、setData関数をいちいち呼ばなければならない。
初期化をいちいち行うのは手間がかかるので、C++ではクラス生成時に呼び出されるコンストラクタというものを定義できる。

> コンストラクタの書き方

クラスの名前(引数){
    初期化処理...
}

> Vector2クラスのコンストラクタ例

```cpp
#include <iostream>

class Vector2{
public:
	int x;
	int y;
	
	Vector2(int _x, int _y){
		x = _x;
		y = _y;
	}
};

int main(){

    Vector2 obj(1, 2);
    std::cout << obj.x << " " << obj.y << std::endl;
    
    return 0;
}
```

## アクセス修飾子

publicやprivateをアクセス修飾子と言う。 publicの要素はクラス外からアクセスでき（公開）、 privateの要素はクラス外からアクセスできない（非公開）。 何も指定されていなければprivateメンバになる。
privateメンバ変数を用いることで、外から直接書き換えられたくないメンバ変数を書き換えることが出来ないようにできる。  
privateは隠蔽、カプセル化などにおいて重要な機能だが、この講座では割愛する(基本的に全てpublicを使い、privateはあまり使用しない)。  

```cpp
#include <iostream>

class MyClass
{
	int a;
public:
	int b;
private:
	int c;
};

int main(){

    MyClass obj;
    
    //コメントを外すとコンパイルエラー
    
    //obj.a = 100;
    //obj.c = 100;

    obj.b = 100;
    
    return 0;
}
```

> 以下のようにすると、クラスの外から値を参照できるが、書き換えることは出来ないようにできる。  

```cpp
#include <iostream>

class MyClass
{
private:
	int data;
public:
	MyClass(){
		data = 3;
	}
	int getData(){
		return data;
	}
};

int main(){

    MyClass obj;
    
    // コメントを外すとコンパイルエラー
    // obj.data = 100;

    std::cout << obj.getData() << std::endl;
    
    return 0;
}
```

## const変数

constをつけると値を変更不可能な変数を作ることができる。#defineの代わりに使って、定数を設定する時などに使える。  

```cpp
#include <iostream>

int main(){

	const int a = 100;

	//コメントを外すとコンパイルエラー
	//a = 200;

	std::cout << "aの値は:" << a << std::endl;

	return 0;
}
```

## 演習問題(コンソール)

1. 以下のプログラムをstd::coutとstd::cinを使って書き直せ。  
		#include <iostream>

		int main() {
			int input; //入力用

			printf("整数値を入力してください：");
			scanf("%d", &input);

			printf("入力された値は、%dです。\n", input);

			return 0;
		}
1. 以下の様なクラスVector3を作った。  
適当なコンストラクタを作れ。  
x,y,zの値を表示するメンバ関数showを作り、動作を確認せよ。  
x\*y\*zの値を表示するメンバ関数showMultipleを作り、動作を確認せよ。  

		class Vector3{
		public:
			int x, y, z;
		};


## 演習問題(DxLib)

1. 以下の様なPlayerクラスを作り、矢印キーで動くようにせよ。

		class Player{
		public:
			double x, y, speed;

			Player(){
				x = 320.0;
				y = 240.0;
				speed = 5.0;
			}
			void update(){
				//ここを実装
				//矢印キーで移動
			}
			//自機（円）を描画
			void draw(){
				DrawCircle(x, y, 30.0, 0x0000FF, 1);
			}
		};

1. Playerクラスの実体を作り、メインループ内でupdate関数とdraw関数を呼び出してPlayerクラスを動作させよ。(ヒント：while内でプレイヤーのインスタンスを作成すると、毎フレーム破棄されてしまう)

1. 以下の様なEnemyクラスを作り、Playerクラスと同様に実体を作り動作を確認せよ。  
今回作るEnemyはただ下に移動するだけでよい。

		class Enemy{
		public:
			double x, y;

			//ここに座標を指定できるようなコンストラクタを実装	

			void update(){
				//ここを実装
				//下方向に移動
			}
			//敵（円）を描画
			void draw(){
				DrawCircle(x, y, 30.0, 0xFF0000, 1);
			}
		};

