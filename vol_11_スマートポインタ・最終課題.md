#　C++DxLib講座資料

##スコープ

下の例では、aは{}内で宣言されているので、{}を抜けるとaが破棄され、aにアクセスできなくなる。

```cpp
#include <iostream>

int main(){

	{
		int a = 30;
		std::cout << "aの値は:" << a << std::endl;
	}
	
	//コメントを外すとコンパイルエラー
	//a = 60;

	return 0;
}
```

下の例では、objは{}内で宣言されているので、{}を抜けるとobjが破棄され、デストラクタが呼ばれる。

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

	{
		std::cout << "スコープに入りました" << std::endl;
		MyClass obj(100);
		std::cout << "objのxの値:" << obj.x << std::endl;
		std::cout << "スコープを抜けます" << std::endl;
	}
	
	//コメントを外すとコンパイルエラー
	//obj.x = 200;
	
	std::cout << "メイン関数を抜けます" << std::endl;

	return 0;
}
```

下の例では、ptrは{}内で宣言され、オブジェクトは{}内でnewされているが、{}を抜ける時破棄されるのがptrなので、{}を抜ける時にオブジェクトのデストラクタが呼ばれない。
つまり、newで確保された領域はdeleteしていないので、開放されていない。

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

	{
		std::cout << "スコープに入りました" << std::endl;
		MyClass *ptr = new MyClass(100);
		std::cout << "objのxの値:" << ptr->x << std::endl;
		std::cout << "スコープを抜けます" << std::endl;
	}
	
	std::cout << "メイン関数を抜けます" << std::endl;

	return 0;
}
```

##スマートポインタ std::shared_ptr

newしたポインタは必ずdeleteしなくてはいけない。これは非常に面倒だし、忘れるとメモリリークの原因になる。そんな時に便利なのがスマートポインタだ。  
スマートポインタはほぼ通常のポインタと同じ使い方でしかも適切なタイミングで自動的にdeleteされる。  

スマートポインタを使用するにはmemoryヘッダーをインクルードする。  

スコープを抜ける時自動的にsptrが破棄され、newで確保したMyClassを指すスマートポインタがなくなるので、自動的にnewで確保した領域が開放される。  

```cpp
#include <iostream>
#include <memory>

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

	{
		std::cout << "スコープに入りました" << std::endl;
		std::shared_ptr<MyClass> sptr( new MyClass(100) );
		std::cout << "objのxの値:" << sptr->x << std::endl;
		std::cout << "スコープを抜けます" << std::endl;
	}
	
	std::cout << "メイン関数を抜けます" << std::endl;

	return 0;
}
```


上の例ではshared_ptrに直接newのポインタを渡して、  

```cpp
std::shared_ptr<MyClass> sptr( new MyClass(100) );
```

のように書いているが、これだと例外に対して脆弱なので、std::make_shared関数を使って、  

```cpp
std::shared_ptr<MyClass> sptr = std::make_shared<MyClass>(100);
```

と書いたほうが良い。  


>書き方

```cpp
std::shared_ptr<クラス名> 変数名 = std::make_shared<クラス名>(引数1, 引数2, ...);
```

##演習問題(コンソール)

1. 以下のような2次元座標を表すVector2クラスを用意した。Vector2クラスへのスマートポインタを要素に持つvectorを用意し、適当な座標を10個ほどmake_sharedで動的確保して追加し、表示せよ。

```cpp
class Vector2{
public:
	int x, y;
	Vector2(int _x, int _y)
	:x(_x),
	y(_y)
	{
	}
	~Vector2() {
		std::cout << "Vector2のデストラクタが呼ばれました" << std::endl;
	}
};
```

1. 上記のvectorの中でx > yとなっている要素を削除せよ。


##演習問題(DxLib)

1. 前回の課題を、Enemyのクラスへのスマートポインタを要素に持つvectorを使って書き直せ。  

## 最終課題
前半課題をポリモーフィズムを用いて書き直せ。練習として、敵の基底クラスへのスマートポインタのvectorに派生クラスを入れ、敵の削除にはremove_ifとラムダ式を使うこと。解答例は例のごとく添付資料内にある。  
