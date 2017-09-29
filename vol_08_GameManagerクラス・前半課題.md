# C++DxLib講座資料　　

## GameManagerクラス

実際ゲームを作る時、PlayerやEnemyの配列、Bulletの配列、Effectの配列等をメンバに持ち、それらを管理するManagerクラスを作ると便利である。  
今回は、PlayerとEnemyを持つManagerクラスの実体をグローバル変数にすることで、EnemyがPlayerが相互にアクセスする例を示す。
(前回は、EnemyクラスがPlayerへのポインタを持つことで、Playerクラスにアクセスすることができたが、今回はEnemyクラスがPlayerクラスへのポインタを持つ必要はない)  
PlayerがEnemyの情報に、EnemyがPlayerの情報に相互にアクセス出来るようにするため、上手くファイルをインクルードしなければならない。  
以下の例では、PlayerはshowEnemyX関数でEnemyのxにアクセスし、EnemyはshowPlayerX関数でPlayerのxにアクセスしている。  


> Player.h

```cpp
#pragma once
#include <iostream>
#include "Manager.h"

class Player {
public:
	int x;
	Player(int _x);
	void update();
	void showEnemyX();
};
```

> Player.cpp

```cpp
#include "Manager.h"

Player::Player(int _x) :
	x(_x)
{
}

void Player::update() {
	std::cout << "Player内のupdateが呼ばれました。xは:" << x << std::endl;
}

void Player::showEnemyX() {
	std::cout << "Player内のshowEnemyXが呼ばれました。" << std::endl;
	std::cout << "Enemyのxは：" << manager.enemy.x << std::endl;
}
```

> Enemy.h

```cpp
#pragma once
#include <iostream>
#include "Manager.h"

class Enemy {
public:
	int x;
	Enemy(int _x);
	void update();
	void showPlayerX();
};
```

> Enemy.cpp

```cpp
#include "Manager.h"

Enemy::Enemy(int _x) :
	x(_x)
{
}

void Enemy::update() {
	std::cout << "Enemy内のupdateが呼ばれました。xは:" << x << std::endl;
}

void Enemy::showPlayerX() {
	std::cout << "Enemy内のshowPlayerXが呼ばれました。" << std::endl;
	std::cout << "Playerのxは：" << manager.player.x << std::endl;
}
```


> Manager.h

```cpp
#pragma once
#include "Player.h"
#include "Enemy.h"

class Manager {
public:
	Player player;
	Enemy enemy;

	Manager();
};

extern Manager manager;
```

> Manager.cpp

```cpp
#include "Manager.h"

Manager::Manager() :
	player(100),
	enemy(200)
{
};

Manager manager;
```

> main.cpp

```cpp
#include <iostream>
#include "Manager.h"

int main() {

	manager.player.update();
	manager.enemy.update();

	manager.player.showEnemyX();
	manager.enemy.showPlayerX();

	return 0;
}
```


## Tips : range-based-for

これまでvectorに対して、for文で用いる時、毎回始めのイテレータと終わりのイテレータを書いていたが、これは面倒である。C++にはrange-based-forがありこれを用いると、配列のそれぞれの要素に対して行う処理が簡単に書ける。以下に書き方を示す。  

```cpp
for(配列の要素の型 受け取る変数 : 配列名){

}
```

以下にサンプルコードを用意した。今回は、自分で用意したMyClass型のvectorのそれぞれの要素のaを表示している。配列の要素の型はautoで推論している。constを使うことで値を間違って変更することを防いでおり、参照を用いて、無駄なコピーをが発生しないようにしている。

```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
	int a;
	MyClass(int _a) :
		a(_a) 
	{
	}
};

int main() {

	std::vector<MyClass> vec;
	for (int i = 0; i < 5; i++) {
		vec.emplace_back(MyClass(i));
	}

	for (const auto& i : vec) {
		std::cout << i.a << std::endl;

		// コメントを外すと値を書き換えることになるのでコンパイルエラー
		// i.a = 99;
	}

	return 0;
}
```

以下はMyClassのaを全て2倍にする例。参照を用いて、vectorの中身を書き換えている。```auto&&```と、&が1つではなく2つあるがタイプミスではない。今回の場合```auto&```でも問題ないが、```auto&&```を用いると右辺値にも対応できるようになり、より汎用的な書き方になるので、range-based-forを用いる際は基本的にこちらを推奨する。(ちなみに、VisualStudio上でマウスカーソルを```i```の上に持っていくとわかるが、```i```はちゃんとMyClass&と推論されていることがわかる)詳しくは、[range-based for loopsの要素の型について](http://qiita.com/rinse_/items/cdfce8aa6a685a8ebe0c)参照。

```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
	int a;
	MyClass(int _a) :
		a(_a) 
	{
	}
};

int main() {

	std::vector<MyClass> vec;
	for (int i = 0; i < 5; i++) {
		vec.emplace_back(MyClass(i));
	}

	// 参照を用いてそれぞれのMyClassのaを2倍に
	for (auto&& i : vec) {
		i.a *= 2;
	}

	// 中身を表示
	for (const auto& i : vec) {
		std::cout << i.a << std::endl;
	}

	return 0;
}

```




## 演習問題(DxLib)

1. GameManagerクラスを作れ。  
GameManagerクラスは、PlayerやEnemyManager(Enemyのvectorを管理するクラス)をメンバに持ち、それらを管理するクラスである。  
GameManagerのインスタンスをグローバル変数にすることで、GameManagerを介してPlayerやEnemyの情報にアクセスできるようにせよ。  
GameManagerクラスのupdateを呼べば、PlayerとすべてのEnemyのupdateが呼ばれるようにせよ。  
EnemyクラスがPlayerクラスへのポインタを持っていた場合、それを消して、Playerクラスへのアクセスはグローバル空間に存在するGameManagerクラスのインスタンスを介して行うようにせよ。  

1. Enemyが自機を追うようにせよ。

1. Enemyクラス内にint型のkind変数を作り、kind変数によって敵が多様な動きをするようにせよ。  
(kind==1なら自機に直進、kind==2ならsin軌道、kind==3なら出た位置で円運動…など)  

1. kindによって敵の色が変わるようにせよ。  

1. kindをenum型にせよ。クラス内で定義されたenumは、クラス外部からは(クラス名)::(要素の名前)でenumを指定できる。  


## ヒント：enum型  

クラス内でenumを定義しコンストラクタで指定する例。  
  
```cpp
#include <iostream>

class Hoge {
public:
	enum Kind {
		A,
		B,
		C,
	};

	Kind kind;

	//コンストラクタ　kindを指定
	Hoge(Kind _kind) :
	kind(_kind)
	{
	}
};

int main() {
	// コンストラクタでkindを指定
	Hoge ins(Hoge::B);

	// 出力。整数が出力される（0から始まる）
	std::cout << ins.kind << std::endl;

	return 0;
}
```


## 前半課題

これまでやったことを用いて、添付資料のサンプルゲームと似たようなものを作れ。今回は練習として、GameManagerクラスが他のクラスを持つ形にすること。  

> ヒント
解答例は以下のようなクラス構成にした。  

GameManagerクラス(他のクラスを所持し、管理する）  
  |- Playerクラス  
  |- PlayerBulletManagerクラス(PlayerBulletクラスのvectorを所持)  
  |- EnemyManagerクラス(Enemyクラスのvectorを所持)  
  |- EnemyBulletManagerクラス(EnemyBulletクラスのvectorを所持)  
  |- EffectManagerクラス(Effectクラスのvectorを所持)  
  |- ScoreManagerクラス(スコアを管理するクラス)  
