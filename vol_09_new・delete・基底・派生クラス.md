# DXライブラリで学ぶC++

## newとdelete

newを使うと、プログラムの実行中にメモリを確保し、オブジェクトを生成できる。
newすると生成したオブジェクトへのポインタが返ってくる。生成したオブジェクトを見失わないように、ポインタを格納する変数を用意する必要がある。

```cpp
#include <iostream>

class MyClass{
public:
	int x;

	MyClass(int _x):
	x(_x)
	{
	}

};

int main(){

	MyClass* ptr = new MyClass(32);
	
	std::cout << "MyClassのxの値 : " << ptr->x << std::endl;
	
	return 0;
}
```

deleteを使うと、プログラム実行中にnewで確保された領域を開放することが出来る。  
deleteには開放する領域のポインタを渡す。  
下の例では、xの値を表示した後deleteするので、メイン関数を抜ける前にデストラクタが呼ばれる。  
deleteされた後にptrのxの値を表示するとカオスな値が入っている（動作未定義）。見てみよう。  
deleteしなかったらデストラクタがいつ呼ばれるか確認してみよう。  

```cpp
#include <iostream>

class MyClass{
public:
	int x;
	
	MyClass(int _x):
	x(_x)
	{
		std::cout << "コンストラクタが呼ばれました" << std::endl;
	}
	
	~MyClass(){
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};

int main(){
	std::cout << "メイン関数に入りました" << std::endl;

	MyClass* ptr = new MyClass(12);
	
	std::cout << "MyClassのxの値 : " << ptr->x << std::endl;
	
	delete ptr;

	std::cout << "メイン関数を抜けました" << std::endl;

	return 0;
}
```

## 演習問題(コンソール)

1. 以下のようなクラスを定義した。MyClassへのポインタのvectorを用意し、適当な値のa(0~10ぐらい)を持ったデータ10個をnewで生成・格納し、表示した後にaが5以下の要素を削除せよ。  

```cpp
#include <iostream>

class MyClass{
public:
	int a;

	MyClass(int _a):
		a(_a)
	{
	}
};
```


> ヒント：vectorの要素のMyClassへのポインタを削除しただけでは動的に確保した領域は解放されていない。remove_ifを用いた形式だと、削除する要素それぞれに対してdeleteを行えないので、Vol6で紹介したwhileループを用いた形式でvectorの要素を削除するとよい。

	auto it = vec.begin();
	while(it != vec.end()){
		if(条件){
			it = vec.erase(it);
		}else{
			it++;
		}
	}


## 基底クラスと派生クラス

クラスを継承することで、新しいクラスを定義することが出来る。  
継承元のクラスを基底クラス、継承先のクラスを派生クラスという。  
派生クラスは基底クラスのメンバを持つ。  

下の例の場合DerivedクラスがBaseクラスを継承している。

```cpp
#include <iostream>

class Base{
public:
	Base(int _x):
		x(_x)
	{
	}
	int x;
	void show(){
		std::cout << "x:" << x << std::endl;
	}
};

class Derived : public Base{
public:
	Derived(int _x):
		Base(_x)
	{
	}
};


int main(){

	Base obj_b(12);
	obj_b.show();

	Derived obj_d(23);
	obj_d.show();

	return 0;
}
```

> 書き方

```cpp
class 派生クラス名 : アクセス 基底クラス名{
public:
	派生クラス名(引数1,引数2, ...):
		基底クラス名(引数1,引数2, ...)
	{
	}
};
```

上記の基底クラス名(引数1,引数2, ...)　で基底クラスのコンストラクタを呼ぶことが出来る。  
基底クラス名(引数1,引数2, ...)　には基底クラスに渡す引数を書く。
アクセスがpublicだと基本クラスのpublicメンバが派生クラスのpublicメンバに、privateだと基本クラスのpublicメンバが派生クラスのprivateメンバになる。

## 演習問題(DxLib)
今回はEnemyを複数出すだけなので、前半課題とは別に、サンプルプロジェクトを元にを作った方が楽かもしれない。  
以下のようなEnenyクラスを用意した。


> Enemy.h

```cpp
#pragma once
#include <DxLib.h>

class Enemy {
public:
	static const double Radius;

	double x, y;
	double vx, vy;
	Enemy(double _x, double _y);
	void update();
	void draw();
};
```

> Enemy.cpp

```cpp
# include "Enemy.h"

const double Enemy::Radius = 30.0;

Enemy::Enemy(double _x, double _y):
	x(_x),
	y(_y),
	vx(0.0),
	vy(0.0),
{
	// 適当な速度を設定
	vx = (double)(rand() % 10 - 5);
	vy = (double)(rand() % 10 - 5);
}

void Enemy::update() {
	x += vx; y += vy;
}

void Enemy::draw() {
	DrawCircle(x, y, 30.0, 0xFF0000, 1);
}

```

1. Enemy型へのポインタを要素に持つvectorを用意し、newを使って敵を複数生成せよ。 

1. 画面外に行った敵を削除せよ。newで動的確保した領域もdeleteで解放すること。

