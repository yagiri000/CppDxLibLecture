#C++講座資料 vol_10

##スコープ（復習）

下の例では、aは{}内で宣言されているので、{}を抜けるとaが破棄され、aにアクセスできなくなる。

```cpp
#include <iostream>

int main(void){

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

class myclass{
public:
	int x;
	myclass(int xx):
		x(xx)
	{
		std::cout << "コンストラクタが呼ばれました" << std::endl;
	}

	~myclass(){
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};


int main(void){

	std::cout << "メイン関数に入りました" << std::endl;

	{
		std::cout << "スコープに入りました" << std::endl;
		myclass obj(100);
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

class myclass{
public:
	int x;
	myclass(int xx):
		x(xx)
	{
		std::cout << "コンストラクタが呼ばれました" << std::endl;
	}

	~myclass(){
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};


int main(void){

	std::cout << "メイン関数に入りました" << std::endl;

	{
		std::cout << "スコープに入りました" << std::endl;
		myclass *ptr = new myclass(100);
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

スコープを抜ける時自動的にsptrが破棄され、newで確保したmyclassを指すスマートポインタがなくなるので、自動的にnewで確保した領域が開放される。  

```cpp
#include <iostream>
#include <memory>

class myclass{
public:
	int x;
	myclass(int xx):
		x(xx)
	{
		std::cout << "コンストラクタが呼ばれました" << std::endl;
	}

	~myclass(){
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};


int main(void){

	std::cout << "メイン関数に入りました" << std::endl;

	{
		std::cout << "スコープに入りました" << std::endl;
		std::shared_ptr<myclass> sptr( new myclass(100) );
		std::cout << "objのxの値:" << sptr->x << std::endl;
		std::cout << "スコープを抜けます" << std::endl;
	}
	
	std::cout << "メイン関数を抜けます" << std::endl;

	return 0;
}
```


上の例ではshared_ptrに直接newのポインタを渡して、  

```cpp
std::shared_ptr<myclass> sptr( new myclass(100) );
```

のように書いているが、これだと例外に対して脆弱なので、std::make_shared関数を使って、  

```cpp
std::shared_ptr<myclass> sptr = std::make_shared<myclass>(100);
```

と書いたほうが良い。  


>書き方

```cpp
std::shared_ptr<クラス名> 変数名 = std::make_shared<クラス名>(引数1, 引数2, ...);
```

##演習問題

1. 2次元座標を表すpointクラスを用意し、pointクラスへのスマートポインタを要素に持つvectorを用意し、適当な座標を10個ほどmake_sharedで動的確保して追加し、表示しなさい。
1. 上記のvectorの中でx > yとなっている要素を削除しなさい。


##演習問題(DXライブラリ)

1. enemyのクラスへのスマートポインタを要素に持つvectorを用意し、敵を複数生成せよ。  
