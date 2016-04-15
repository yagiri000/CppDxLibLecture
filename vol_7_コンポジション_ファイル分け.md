#cpp講座資料　vol_7

実際にゲームを作る時、ファイル分けをすることが必要になる。  
今回はクラスの内容を.hと.cppに分け、それが必要なケースと、なぜ必要になるのかを解説する。      
若干ややこしい話になるので、指示をよく聞き、指示通りにファイルの位置を配置すること。  



##ファイル分け
以下のように、.hと.cppにクラスの定義を分けて書くことが出来る。  
.cppには、クラス名::関数名と書く必要がある。  

>player.h

```cpp
#include <iostream>

class player{
public:	
	int x, y;

	player(int xx, int yy);

	void update();

	void draw();

	void show_xy();
};
```

>player.cpp

```cpp
#include "player.h"

player::player(int xx, int yy) :
x(xx),
y(yy)
{
}

void player::update(){
	std::cout << "playerのupdateが呼ばれました。" << std::endl;
}

void player::draw(){
	std::cout << "playerのdrawが呼ばれました。" << std::endl;
}

void player::show_xy(){
	std::cout << "playerのshow_xyが呼ばれました。 x:" << x << " y:" << y << std::endl;
}
```

>main.cpp

```cpp
#include <iostream>
#include "player.h"

int main(void){

	player ply(20, 30);

	ply.update();

	ply.draw();

	ply.show_xy();

	return 0;
}
```

##コンポジション
クラスをクラスのメンバにすることが出来る。  
以下の例では、pointクラスをまず定義し、playerクラスでpointクラスのメンバを持っている。  

```cpp
#include <iostream>

class point{
public:
	int x, y;
	point(int xx, int yy) :
		x(xx),
		y(yy)
	{
	}
};

class player{
public:
	point pt;
	int hp;

	player(int x, int y, int hp_) :
		pt(x, y),
		hp(hp_)
	{
	}
};


int main(void){
	player ply(100, 200, 64);

	std::cout << "x:" << ply.pt.x << ", y:" << ply.pt.y << std::endl;
	std::cout << "hp:" << ply.hp << std::endl;

	return 0;
}

```

コンストラクタは以下のように書く。引数を受け渡すと考えれば良い。  
classAがclassBを持つ場合  

```cpp
classA(引数1,引数2,引数3...) :
	classB(引数1,引数2,引数3...)
	{
	}
```

クラスをコンポジションした場合、クラスに含まれているクラスのコンストラクタが先に呼ばれる。デストラクタは逆の順で呼ばれる。  
hogeやpiyoは日本では、「特に意味のない名前」を表す。  

```cpp
#include <iostream>

class hoge{
public:
	int x;

	hoge(int xx):
		x(xx)
	{
		std::cout << "hogeのコンストラクタが呼ばれました" << std::endl;
	}

	~hoge(){
		std::cout << "hogeのデストラクタが呼ばれました" << std::endl;
	}
};

class piyo{
public:
	hoge hoge_;
	int y;

	piyo(int xx, int yy):
		hoge_(xx),
		y(yy)
	{
		std::cout << "piyoのコンストラクタが呼ばれました" << std::endl;
	}

	~piyo(){
		std::cout << "piyoのデストラクタが呼ばれました" << std::endl;
	}
};


int main(void){

	piyo piyo_(100, 200);

	std::cout << piyo_.hoge_.x << " " << piyo_.y << std::endl;

	return 0;
}
```


##インクルード
\#includeを使うと自分が定義したヘッダーをインクルードできる。インクルードすると、その部分にヘッダーの中身のコードが展開される。

##\#pragma once
\#pragma onceを使うと一度読み込まれたヘッダーは読み込まれないようになる。複数のファイルから読み込まれるヘッダーの一番上につけることで、多重定義を防ぐことが出来る。  
以下の例では、playerクラスとenemyクラスで共通で使うpointクラスを作り、それをどちらのファイルからも読み込んでいる。  
pointクラスのpragma onceを外すと、コンパイルエラーが起きる。  

>point.h

```cpp
#pragma once
#include <iostream>

class point{
public:
	int x, y;
	point(int xx, int yy) :
		x(xx),
		y(yy)
	{
	}
};
```

>enemy.h

```cpp
#include <iostream>
#include "point.h"

class enemy{
public:
	point pt;

	enemy(int x, int y) :
		pt(x, y)
	{
	}
};
```

>player.h

```cpp
#include <iostream>
#include "point.h"

class player{
public:
	point pt;

	player(int x, int y) :
		pt(x, y)
	{
	}
};
```

>main関数内

```cpp
#include <iostream>
#include "player.h"
#include "enemy.h"


int main(void){

	player ply(100, 200);
	enemy emy(300, 400);

	std::cout << ply.pt.x << ", " << ply.pt.y << std::endl;
	std::cout << emy.pt.x << ", " << emy.pt.y << std::endl;

	return 0;
}
```



##まとめ
* クラスが他のクラスを実体としてメンバとして持つ、または他のクラスのメンバにアクセスするときは、他のクラスの定義がクラスの前方（コードの上のほう）になければならない。　　
* 実際にゲームを作るときは、とりあえず#pragma onceをつけよう。#pragma onceは特に害はない。  



##GameManagerクラス
実際ゲームを作る時、playerやenemyの配列、bulletの配列、effectの配列等をメンバに持ち、それらを管理するmanagerクラスを作ると便利である。  
今回は、managerクラスをシングルトンにすることで、enemyがplayerにアクセスしたいときに、managerクラスを介してplayerクラスにアクセス出来るようにしたい。また、同様にplayerクラスがenemyクラスにアクセス出来るようにしたい。  
(前回は、enemyクラスがplayerへのポインタを持つことで、playerクラスにアクセスすることができたが、今回はenemyクラスがplayerクラスへのポインタを持つ必要はない)　　
playerがenemyの情報に、enemyがplayerの情報に相互にアクセス出来るようにするため、上手くファイルをインクルードしなければならない。  
以下の例では、playerはshowenemyx関数でenemyのxにアクセスし、enemyはshowplayerx関数でplayerのxにアクセスしている。  


>player.h

```cpp
#pragma once
#include <iostream>
#include "manager.h"

class player{
public:
	int x;

	player(int xx);
	void update();
	void showenemyx();

};
```

>player.cpp

```cpp
#include "manager.h"

player::player(int xx) :
x(xx)
{
}

void player::update(){
	std::cout << "player内のupdateが呼ばれました。xは:" << x << std::endl;
}

void player::showenemyx(){
	std::cout << "player内のshowenemyxが呼ばれました。" << std::endl;
	std::cout << "enemyのxは：" << manager::get().enemy_.x << std::endl;
}
```

>enemy.h

```cpp
#pragma once
#include <iostream>
#include "manager.h"

class enemy{
public:
	int x;

	enemy(int xx);
	void update();
	void showplayerx();

};
```

>enemy.cpp

```cpp
#include "manager.h"

enemy::enemy(int xx) :
x(xx)
{
}

void enemy::update(){
	std::cout << "enemy内のupdateが呼ばれました。xは:" << x << std::endl;
}

void enemy::showplayerx(){
	std::cout << "enemy内のshowplayerxが呼ばれました。" << std::endl;
	std::cout << "playerのxは：" << manager::get().player_.x << std::endl;
}
```


>manager.h

```cpp
#pragma once
#include <iostream>
#include "player.h"
#include "enemy.h"

class manager{
public:
	static manager& get(){
		static manager inst;
		return inst;
	}
	
	manager(const manager& r) = delete;//コピー禁止
	manager& operator=(const manager& r) = delete;//代入禁止
	
	player player_;
	enemy enemy_;


private:
	manager() :
		player_(100),
		enemy_(200)
	{
	};
};
```

>main.cpp

```cpp
#include <iostream>
#include "manager.h"

int main(){

	manager::get().player_.update();
	manager::get().enemy_.update();

	manager::get().player_.showenemyx();
	manager::get().enemy_.showplayerx();

	return 0;
}
```

##演習問題  

* 上記のplayerクラスのx, enemyクラスのxはpublicメンバで、直接書き換えることが可能であり、危険である。  
この2つをprivateメンバにし、外から値が取得できるようにgetx()関数を実装せよ。  


##演習問題(DXライブラリ)

* GameManagerクラスを作れ。  
GameManagerクラスは、playerやenemymanagerをメンバに持ち、それらを管理するクラスである。    
GameManagerをシングルトンにすることで、GameManagerを介してplayerやenemyの情報にアクセスできるようにせよ。  
GameManagerクラスのupdateを呼べば、playerとすべてのenemyのupdateが呼ばれるようにせよ。  
enemyクラスがplayerクラスへのポインタを持っていた場合、それを消して、playerクラスへのアクセスはGameManagerクラスを介して行うようにせよ。  