#C++講座資料 vol_1

今回はC++でのHello World、クラスの基本的な使い方について学ぶ。
演習では、実際にDXライブラリを用いてplayer,enemyを生成する。

##Hello World!

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

##いろいろ出力

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

##入力

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

##クラスの基本的な書き方

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

	MyClass obj;
	obj.a = 10;
	obj.b = 20;
	std::cout << obj.a << " " << obj.b << std::endl;
	
	return 0;
}
```

二次元上の座標を表すクラス、Pointを作った。  
クラスの要素には```.```（コンマ）を使ってアクセスできる。  
クラスは関数を要素に持つことができ、メンバ関数という。（下の例ではsetdata関数がメンバ関数）  

```cpp
#include <iostream>

class Point{
public:
	int x;
	int y;
	void setdata(int xx, int yy){
		x = xx;
		y = yy;
	}
};

int main(){

	Point obj;
	obj.setdata(13, 29);
	std::cout << obj.x << " " << obj.y << std::endl;
	
	return 0;
}
```

##コンストラクタ

さっきの例ではPointクラスを作った後、setdata関数をいちいち呼ばなければならない。
初期化をいちいち行うのは手間がかかるので、C++ではクラス生成時に呼び出されるコンストラクタというものを定義できる。

>コンストラクタの書き方

クラスの名前(引数){
    初期化処理...
}

>pointクラスのコンストラクタ例

```cpp
#include <iostream>

class point{
public:
	int x;
	int y;
	
	point(int xx, int yy){
		x = xx;
		y = yy;
	}
};

int main(){

    point obj(1, 2);
    std::cout << obj.x << " " << obj.y << std::endl;
    
    return 0;
}
```

##アクセス修飾子

publicやprivateをアクセス修飾子と言う。 publicの要素はクラス外からアクセスでき（公開）、 privateの要素はクラス外からアクセスできない（非公開）。 何も指定されていなければprivateメンバになる。

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

>publicメンバ関数を通じて非公開メンバにアクセス可能。

```cpp
#include <iostream>

class MyClass
{
	int a;
public:
	int b;
	void setdata(int a_, int b_, int c_){
		a = a_;
		b = b_;
		c = c_;
	}
	
	void showdata(){
		std::cout << a << " " << b << " " << c << " " << std::endl;
	}
private:
	int c;
};

int main(){

    MyClass obj;
    
    //コメントを外すとコンパイルエラー
    
    //obj.a = 100;
    //obj.c = 100;

    obj.setdata(6, 13, 20);
    obj.showdata();
    
    return 0;
}
```

##const変数

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

##演習問題

1. 以下のプログラムをstd::coutとstd::cinを使って書き直せ。  

		#include <iostream>

		int main() {
			int input; //入力用

			printf("整数値を入力してください：");
			scanf("%d", &input);

			printf("入力された値は、%dです。\n", input);

			return 0;
		}


1. 以下の様なクラスPoint3を作った。  
適当なコンストラクタを作れ。  
x,y,zの値を表示するメンバ関数showを作れ。  
x\*y\*zの値を表示するメンバ関数show_multipleを作れ。  

		class Point3{
		public:
			int x, y, z;
		};


##演習問題(DXライブラリ)

1. 以下の様なPlayerクラスを作り、矢印キーで動くようにせよ。

		class Player{
		public:
			double x, y;

			Player(){
				x = 200;
				y = 200;
			}
			void update(){
				//ここを実装
				//矢印キーで移動
				
			}
			//自機（円）を描画
			void draw(){
				DrawCircle(x, y, 10, GetColor(0, 0, 255), 1);
			}
		};

1. Playerクラスの実体を作り、メインループ内でupdate関数とdraw関数を呼び出してplayerクラスを動作させよ。

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
				DrawCircle(x, y, 10, GetColor(255, 0, 0), 1);
			}
		};

1. Player.hとEnemy.hを作り、PlayerクラスとEnemyクラスをファイル分けせよ。
