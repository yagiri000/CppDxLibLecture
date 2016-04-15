#C++講座資料 vol_3

##string型

C++標準ライブラリのstring型を使うと、Cのchar型に比べ、より簡単に文字列を扱うことが出来る。
+演算子で文字列の結合、==演算子で文字列の比較が出来る。  
string型を使用するときは、stringヘッダーをインクルードする。（string.hではないことに注意）

```cpp
#include <iostream>
#include <string>

int main(){
    std::string str1 = "いかろちゃん";
    std::string str2 = "かわいい";
    
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    
    std::string str3;
    // +で文字列の結合ができる
    str3 = str1 + str2;
    
    std::cout << str3 << std::endl;
    
    // ==で文字列の比較ができる trueなので1が出力される
    std::cout << (str3 == (str1+str2)) << std::endl;
    
    return 0;
}
```


>std::to_string関数を使うと、int型、double型等の変数をstring型に変換できる。

```cpp
#include <iostream>
#include <string>

int main(){
    std::string str = "いかろちゃんかわいい";
	int ix = 23;
	double dx = 3.14;
	
	str += " ";
	str += std::to_string(ix);
	str += " ";
	str += std::to_string(dx);
    
    std::cout << str << std::endl;
    
    return 0;
}
```

##bool型
C言語では、0は偽、それ以外は真だったが、C++には真偽を表すためだけの型、bool型が存在する。  


```cpp
#include <iostream>

int main(void){

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

bool iseven(int num){
	return (num % 2) == 0;
}

int main(void){

	if (iseven(10)){
		std::cout << "条件文は真" << std::endl;
	}
	else{
		std::cout << "条件文は偽" << std::endl;
	}

	return 0;
}	
```


##スコープ

{ } で囲まれた部分を抜けると、その{}内部で宣言された変数は破棄されるので、アクセスできなくなる。
変数や関数の「見える」範囲をスコープと言い、変数の寿命はスコープによって決まる。


```cpp
#include <iostream>

void func(){
	int a = 10;
	std::cout << "aの値は " << a << std::endl;
}

int main(){
	
	func();

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

##参照

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

>参照を用いたaとbを入れ替える関数

```cpp
#include <iostream>
//aとbを入れ替える関数
void swap(int& a,int& b){
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

>参照を用いてhogeに別名をつけることが出来る。

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


##演習問題

1. 文字列をうけとりその末尾に「その点トッポってすげぇよな、最後までチョコたっぷりだもん。」と付加するような関数を作れ。  

1. 空の文字列を用意し、入力された文字をその文字列の終端に付け加えていき、"show"と入力されたら現在の文字列を表示せよ。


##ポインタ（復習）

>2通りの方法でaの値とアドレスを表示

```cpp
#include <iostream>

int main(void){

	int a = 100;
	int *ptr = &a;

	//2通りの方法でaの値とアドレスを表示
	std::cout << "aの値:" << a << "  aのアドレス:" << &a << std::endl;
	std::cout << "aの値:" <<  *ptr << "  aのアドレス:" << ptr << std::endl << std::endl;

	return 0;
}
```

##オブジェクトへのポインタ

オブジェクトを指すポインタからオブジェクトの要素にアクセスしたい時がある。  
下の例では、オブジェクトを指すポインタ、ptrから、objのxにアクセスしたい。  
(\*ptr).xと書けばobjのxにアクセスできるが、少々書きづらいので、  
ptr->xと書くことができるようになっている。  
(\*ptr).x と ptr->x は同じ意味である。  
-> をアロー演算子という。  

ちなみに、\*ptr.xと書くと\*(ptr.x)と解釈され、ptrのx（存在しない）が指すものを表す。

```cpp
#include <iostream>

class point{
public:
	int x, y;

	point(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};

int main(void){

	point obj(12, 34);
	point *ptr = &obj;
	
	//普通に表示
	std::cout << obj.x << " " << obj.y << std::endl;

	std::cout << (*ptr).x << " " << (*ptr).y << std::endl;

	std::cout << ptr->x << " " << ptr->y << std::endl;


	//↓このようには書けない。　*(ptr.x)と解釈されるから
	//std::cout << *ptr.x << " " << *ptr.y << std::endl;

	
	return 0;
}
```

##演習問題(DXライブラリ)
（1. 2.…と順番に解いていって下さい。 これまでコードを書いてきたプロジェクトとは別に新しくプロジェクトを作ってください。）

1. string型の変数を用意し、DrawFormatStringToHandle関数を用いて画面中央に表示せよ。はじめの文字列は入力を求めるのではなく、プログラム内で決めてよい。

* DrawFormatStringToHandle関数は引数にstring型ではなくchar\*を取る。  (string型変数).c_str()関数を使うことでstring型の文字列をchar\*へ変換できる。

	>例

	```cpp
	string str = "aaa";
	DrawFormatStringToHandle( x , y , Color , FontHandle , str.c_str() ) ;
	```


1. Xキーを押した時に、上記の文字列の末尾に「かわいい」が追加されるようにせよ。

1. 以下の様なplayerクラスとenemyクラスを用意した。playerクラスとenemyクラスのインスタンスを作り、動作を確認せよ。

>playerクラス

```cpp
class player{
public:
	double x, y;
	double movev;

	player(){
		x = 400;
		y = 500;
		movev = 3;
	}

	void update(){
		if(CheckHitKey(KEY_INPUT_RIGHT) == 1){
			x += movev;
		}
		if(CheckHitKey(KEY_INPUT_LEFT) == 1){
			x -= movev;
		}
		if(CheckHitKey(KEY_INPUT_UP) == 1){
			y -= movev;
		}
		if(CheckHitKey(KEY_INPUT_DOWN) == 1){
			y += movev;
		}
	}

	void draw(){
		DrawCircle(x, y, 10, GetColor(0, 0, 255), 1);
	}

};
```

>enemyクラス

```cpp
class enemy{
public:
	double x, y, vx, vy;
	enemy(double ix, double iy){
		x = ix;
		y = iy;
		vx = 0;
		vy = 1.0;
	}

	void update(){
		x += vx;
		y += vy;
	}

	void draw(){
		DrawCircle(x, y, 24, GetColor(255, 0, 0), 1);
	}

};
```


1. player.hとenemy.hを作り、playerクラスとenemyクラスをファイル分けせよ。

1. enemyがplayerの方向に移動するようにしたい。enemyクラスが「playerクラスへのポインタ」をメンバに持つようにして、playerクラスとenemyクラスのインスタンスを生成した後にenemyのインスタンスににplayerのインスタンスのポインタを渡し、そのポインタからplayerクラスのx,yにアクセスすることでenemyがplayerの位置を取得し、その方向に移動できるようにせよ。  
（今回は、敵の追尾は大まかで良い。例：playerのxがenemyのxより大きければenemyは右に、そうでなければ左に動く…など）

>ヒント

プログラムは、上から順にコンパイラに解釈されていく。enemyクラス内でplayerクラスにアクセスするには、アクセスする前にplayerクラスの中身をコンパイラが知らなければならない。  
今回の場合、WinMainがあるcppの上部で、 \#include "player.h" が \#include "enemy.h" より前に書かれていれば、コンパイラがplayerの中身を知ってからenemy.hを解釈するので問題ない。  
\#include "enemy.h" を \#include "player.h" より前に書きたいときは、enemy.hがインクルードされる前にどこかのヘッダー、またはenemy.hの上部に \#include "player.h" があればよい。  
enemy.hとmain.cppの二箇所からでplayer.hを読み込むときは、多重インクルードを防ぐため、player.hの上部に \#pragma once をつける必要がある。  


>enemy側

```cpp
class enemy{
public:
	double x, y, vx, vy;

	player* pplayer;//これを追加

	//ポインタ取得用関数
	void setplayerptr(player* ptr){
		pplayer = ptr;
	}

	//以下略
};
```

>初期化処理側

```cpp
player ply;//playerのインスタンスを生成
enemy emy;//enemyのインスタンスを生成
emy.setplayerptr(&ply);//ポインタを入れる
```
