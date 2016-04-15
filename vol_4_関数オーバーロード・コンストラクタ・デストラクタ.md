#C++講座資料 vol_4

##関数オーバーロード

C++では、引数が異なる同じ名前の関数を定義できる。そのように関数を多重定義することを関数オーバーロードという。
実行中に、引数によって呼ばれる関数が選択される。

```cpp
#include <iostream>

//絶対値を返す関数、myabsを3通りにオーバーロードする
int myabs(int n){
	std::cout << "int型のmyabsが呼ばれました" << std::endl;
	if(n > 0){
		return n;
	}else{
		return -n;
	}
}

float myabs(float n){
	std::cout << "float型のmyabsが呼ばれました" << std::endl;
	if(n > 0){
		return n;
	}else{
		return -n;
	}
}

double myabs(double n){
	std::cout << "double型のmyabsが呼ばれました" << std::endl;
	if(n > 0){
		return n;
	}else{
		return -n;
	}
}


int main(){

	int a = -10;
	float b = -2.71f;
	double c = -3.14;
	
	std::cout << myabs(a) << std::endl << std::endl;
	std::cout << myabs(b) << std::endl << std::endl;
	std::cout << myabs(c) << std::endl << std::endl;


	return 0;

}
```

>引数の数によって呼ばれる関数が変わる。

```cpp
#include <iostream>

void myfunc(int a){
	std::cout << "引数１つのmyfuncが呼ばれました。引数は " << a << std::endl;
}

void myfunc(int a, int b){
	std::cout << "引数２つのmyfuncが呼ばれました。引数は " << a << " " << b << std::endl;
}

int main(){
	myfunc(1);
	myfunc(2, 3);

	return 0;
}
```


##演習問題

1. 引数で受け取った値の2乗を返す関数mysquare()を作成せよ。mysquare()をint,float,double型の3通りに対応できるようオーバーロードしなさい。


##コンストラクタ

C++ではクラス生成時に呼び出されるコンストラクタというものを定義できる。
関数オーバーロードと同じ要領で、コンストラクタは複数定義できる。

>コンストラクタの書き方

```cpp
クラスの名前(引数){
    初期化処理...
}
```

>obj1は引数(1, 2)で初期化。obj2は引数無しで初期化なので自動的に(0, 0)が入る。

```cpp
#include <iostream>

class point{
public:
	int x;
	int y;
	
	point(){
		std::cout << "引数なしのコンストラクタが呼ばれました" << std::endl;
		x = 0;
		y = 0;
	}
	
	point(int xx, int yy){
		std::cout << "引数ありのコンストラクタが呼ばれました" << std::endl;
		x = xx;
		y = yy;
	}
};

int main(){

    point obj1(1, 2);
    std::cout << obj1.x << " " << obj1.y << std::endl;
    
    point obj2;
    std::cout << obj2.x << " " << obj2.y << std::endl;
    
    return 0;

}
```

>コンストラクタの数値の初期化は以下のようにも書くことができる。  
自分で定義したクラスをなど初期化する場合、こう書いたほうが、インスタンスのコピーが発生しなくなるため処理が早くなる。(このコードはコピペじゃなく実際打ってみよう)

```cpp
#include <iostream>

class point{
public:
	int x;
	int y;
	
	point(int xx, int yy):
	x(xx),
	y(yy)	
	{
		
	}
};

int main(){

    point obj(1, 2);
    std::cout << obj.x << " " << obj.y << std::endl;
    
    return 0;

}
```

##デストラクタ

オブジェクトが破棄されるときにデストラクタが呼ばれる。

>デストラクタの書き方。~(チルダ）をつける

~クラスの名前(){
    処理...
}

>メイン関数を抜ける時オブジェクトが破棄されるのでデストラクタが呼ばれる。

```cpp
#include <iostream>

class myclass{
public:
	~myclass(){
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};

int main(){
	std::cout << "メイン関数に入りました" << std::endl;

	myclass obj;

	std::cout << "メイン関数を抜けました" << std::endl;

	return 0;

}
```


##演習問題

1. 以下の様なクラスpointを作った。コンストラクタとデストラクタを作れ。  
コンストラクタ・デストラクタがよばれたら、"～が呼ばれました"と出力するようにせよ。コンストラクタは引数有りのものと引数なし（引数なしの時はx=0,y=0)のものを作ること。  
コンストラクタの初期化の部分は今回教えた形式で書け。

```cpp
class point{
	public:
		int x, y;

		//以下にコンストラクタとデストラクタ書く
}
```