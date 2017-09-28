# C++DxLib講座資料

## bool型

C++には真偽を表すためだけの型、bool型が存在する。  


```cpp
#include <iostream>

int main(){

	bool b = true;

	if (b){
		std::cout << "条件文は真" << std::endl;
	}
	else{
		std::cout << "条件文は偽" << std::endl;
	}

	return 0;
}
```

以下のように、条件を満たすかどうかの真・偽を返す関数の返り値の型としてbool型を使うことが多い。

```cpp
#include <iostream>

// 偶数だったらtrue,そうでなければfalseを返す関数
bool isEven(int num){
	return (num % 2) == 0;
}

int main(){

	if (isEven(10)){
		std::cout << "条件文は真" << std::endl;
	}
	else{
		std::cout << "条件文は偽" << std::endl;
	}

	return 0;
}	
```


## スコープ

{ } で囲まれた部分を抜けると、その{}内部で宣言された変数は破棄されるので、アクセスできなくなる。
変数や関数の「見える」範囲をスコープと言い、変数の寿命はスコープによって決まる。


```cpp
#include <iostream>

void func()){
	int a = 10;
	std::cout << "aの値は " << a << std::endl;
}

int main(){
	
	func());

	//コメントを外すとコンパイルエラー
	//a = 100;  

	if(true){
		int b = 20;
		std::cout << "bの値は " << b << std::endl;
	}
	
	//コメントを外すとコンパイルエラー
	//b = 100; 

	for(int i = 0; i < 3; i++){
		std::cout << "iの値は " << i << std::endl;
	}
	
	//コメントを外すとコンパイルエラー
	//i = 100; 

	return 0;
}
```


>{}だけでもスコープを作ることができる

```cpp
#include <iostream>

int main(){
	{
		int b = 20;
		std::cout << "bの値は " << b << std::endl;
	}
	
	//コメントを外すとコンパイルエラー
	//b = 100; 

	return 0;
}
```

## 参照

swap関数を実装するためにポインタを用いる事があったかもしれない。 C++ではそれを扱いやすくした参照(リファレンス)というものが存在する。  


>ポインタを用いたaとbを入れ替える関数

```cpp
#include <iostream>
//aとbを入れ替える関数 
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
    return;
}

int main(){
 
    int a=3;
    int b=5;
 
    std::cout << a << "," << b << std::endl;
    
    swap(&a, &b);//aとbのポインタを渡さなければいけない
    
    std::cout << a << "," << b << std::endl;
 
    return 0;
}  
```

>よくない例。下のように書くと、関数内でaとbのコピーが出来て、コピーのaとbが入れ替えられ、関数を抜けた時点で破棄されるので、main関数内のaとbは入れ替えられない。

```cpp
#include <iostream>
//aとbを入れ替える関数 値渡しなので入れ替えられない
void swap(int a,int b){
    int tmp=a;
    a=b;
    b=tmp;
    return;
}

int main(){

    int a=3;
    int b=5;
 
    std::cout << a << "," << b << std::endl;
    
    swap(a, b);
    
    std::cout << a << "," << b << std::endl;
    
    return 0;
}
```

>参照を用いたaとbを入れ替える関数。正しくaとbの値が入れ替わっており、かつポインタを用いた例より読みやすく書けていることがわかる。  

```cpp
#include <iostream>
//aとbを入れ替える関数
void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
	return;
}

int main() {

	int a = 3;
	int b = 5;

	std::cout << a << "," << b << std::endl;

	swap(a, b);

	std::cout << a << "," << b << std::endl;

	return 0;
}
```

>参照を用いてHogeに別名をつけることが出来る。

```cpp
#include <iostream>

int main(){
 
    int hoge = 2;
 
    //aliasはhogeの別名(aliasを操作するとhogeの値が変わる)
    int& alias = hoge;
    
    std::cout << hoge << ", " << alias << std::endl;
    
    alias=4;
    std::cout << hoge << ", " << alias << std::endl;
 
    return 0;
}
```

>ポインタを使っても同じことが出来るが、*や&をつけるのに手間がかかり、ミスをしてバグを起こしやすいので、これからは参照を使おう。

```cpp
#include <iostream>

int main(){
 
    int hoge = 2;
 
    int* ptr = &hoge;
    
    std::cout << hoge << ", " << *ptr << std::endl;
    
    *ptr = 4;
    std::cout << hoge << ", " << *ptr << std::endl;
 
    return 0;
}
```

## const参照渡し

関数・コンストラクタがクラスを引数に取る時、オブジェクトのコピーが発生している。参照渡しを使うと、コピーが発生することを防ぐことが出来、無駄がなくなる。
また、引数にconstを付けると、関数内で値を変更できなくなる。これは間違って値を書き換えてしまうのを防ぐのに有用である。
以下は、const参照渡しを使う関数の例である。本資料では以降クラスを引数に取る時、適宜参照渡し、const参照渡しを使っていく。

```cpp
#include <iostream>

class Color {
public:
	int r, g, b;
	Color(int _r, int _g, int _b) :
	r(_r),
	g(_g),
	b(_b)
	{
	}
};

void showColor(const Color& color) {
	std::cout << "r:" << color.r << " g:" << color.g << " b:" << color.b << std::endl;
	// コメントを外すと値を書き換えることになるのでコンパイルエラー
	// color.r = 0;
}

int main() {

	Color color(150, 100, 50);

	showColor(color);

	return 0;
}
```


## 演習問題(コンソール)

1. 参照でint型をうけとり2倍にする関数を作れ。  


## ポインタ（復習）

>2通りの方法でaの値とアドレスを表示

```cpp
#include <iostream>

int main(){

	int a = 100;
	int *ptr = &a;

	//2通りの方法でaの値とアドレスを表示
	std::cout << "aの値:" << a << "  aのアドレス:" << &a << std::endl;
	std::cout << "aの値:" <<  *ptr << "  aのアドレス:" << ptr << std::endl << std::endl;

	return 0;
}
```

## オブジェクトへのポインタ

オブジェクトを指すポインタからオブジェクトの要素にアクセスしたい時がある。  
下の例では、オブジェクトを指すポインタ、ptrから、objのxにアクセスしたい。  
(\*ptr).xと書けばobjのxにアクセスできるが、少々書きづらいので、  
ptr->xと書くことができるようになっている。  
(\*ptr).x と ptr->x は同じ意味である。  
-> をアロー演算子という。  

ちなみに、\*ptr.xと書くと\*(ptr.x)と解釈され、ptrのx（存在しない）が指すものを表す。

```cpp
#include <iostream>

class Vector2{
public:
	int x, y;

	Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

int main(){

	Vector2 obj(12, 34);
	Vector2 *ptr = &obj;
	
	//普通に表示
	std::cout << obj.x << " " << obj.y << std::endl;

	std::cout << (*ptr).x << " " << (*ptr).y << std::endl;

	std::cout << ptr->x << " " << ptr->y << std::endl;


	//↓このようには書けない。　*(ptr.x)と解釈されるから
	//std::cout << *ptr.x << " " << *ptr.y << std::endl;

	
	return 0;
}
```



## 演習問題(DxLib)

今回は、これまでコードを書いてきたプロジェクトとは別に、プロジェクトを作ることを推奨します。

1. 以下の様なPlayerクラスとEnemyクラスを用意した。PlayerクラスとEnemyクラスのインスタンスを作り、動作を確認せよ。

	>Player.h

		#pragma once
		#include <DxLib.h>

		class Player {
		public:
			static const double Speed;
			Vec2 pos;
			Player();
			void update();
			void draw();
		};

	>Player.cpp

		#include "Player.h"

		const double Player::Speed = 5.0;

		Player::Player() :
		pos(320.0, 240.0)
		{
		}

		void Player::update() {
			// 上下左右キーで移動
			if (Input::KeyLeft.pressed) {
				pos.x -= Speed;
			}
			if (Input::KeyRight.pressed) {
				pos.x += Speed;
			}
			if (Input::KeyUp.pressed) {
				pos.y -= Speed;
			}
			if (Input::KeyDown.pressed) {
				pos.y += Speed;
			}
		}

		void Player::draw() {
			Circle(pos, 30.0).draw(Color(0, 0, 255));
		}

	>Enemy.h

		#pragma once
		#include <DxLib.h>
		#include "Player.h"

		class Enemy {
		public:
			Vec2 pos;
			Vec2 velocity;
			Enemy(const Vec2& _pos);
			void update();
			void draw();
		};

	>Enemy.cpp

		# include "Enemy.h"

		Enemy::Enemy(const Vec2& _pos):
			pos(_pos),
			velocity(0.0, 0.0)
		{
		}

		void Enemy::update() {
			pos += velocity;
		}

		void Enemy::draw() {
			Circle(pos, 30.0).draw(Color(255, 0, 0));
		}


1. EnemyがPlayerの方向に移動するようにしたい。Enemyクラスが「Playerクラスへのポインタ」をメンバに持つようにして、PlayerクラスとEnemyクラスのインスタンスを生成した後にEnemyのインスタンスににPlayerのインスタンスのポインタを渡し、そのポインタからPlayerクラスのx,yにアクセスすることでEnemyがPlayerの位置を取得し、その方向に移動できるようにせよ。  
（今回は、敵の追尾は大まかでも良い。例：PlayerのxがEnemyのxより大きければEnemyは右に、そうでなければ左に動く…など）

>ヒント

プログラムは、上から順にコンパイラに解釈されていく。Enemyクラス内でPlayerクラスにアクセスするには、アクセスする前にPlayerクラスの中身をコンパイラが知らなければならない。よって、Enemy.hからPlayer.hをincludeしている。
Enemy.hとmain.cppの二箇所からPlayer.hを読み込むときは、多重インクルードを防ぐため、Player.hの上部に #pragma once をつける必要がある。


>Enemy側に以下を追加

```cpp
	Player* pPlayer; 

	//ポインタ取得用関数
	void setPlayerPtr(Player* ptr){
		pPlayer = ptr;
	}
```

>初期化処理側

```cpp
Player player;//Playerのインスタンスを生成
Enemy enemy;//Enemyのインスタンスを生成
Enemy.setPlayerPtr(&player);//ポインタを入れる
```
