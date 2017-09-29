# C++DxLib講座資料

今回は関数オーバーロードと、コンストラクタ、デストラクタについて説明する。

## 関数オーバーロード

C++では、引数が異なる同じ名前の関数を定義できる。そのように関数を多重定義することを関数オーバーロードという。
実行中に、引数によって呼ばれる関数が選択される。

```cpp
#include <iostream>

//絶対値を返す関数、myAbsを3通りにオーバーロードする
int myAbs(int n){
	std::cout << "int型のmyAbsが呼ばれました" << std::endl;
	if(n > 0){
		return n;
	}else{
		return -n;
	}
}

float myAbs(float n){
	std::cout << "float型のmyAbsが呼ばれました" << std::endl;
	if(n > 0){
		return n;
	}else{
		return -n;
	}
}

double myAbs(double n){
	std::cout << "double型のmyAbsが呼ばれました" << std::endl;
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
	
	std::cout << myAbs(a) << std::endl << std::endl;
	std::cout << myAbs(b) << std::endl << std::endl;
	std::cout << myAbs(c) << std::endl << std::endl;


	return 0;

}
```

>引数の数によって呼ばれる関数が変わる。

```cpp
#include <iostream>

void myFunc(int a){
	std::cout << "引数１つのmyFuncが呼ばれました。引数は " << a << std::endl;
}

void myFunc(int a, int b){
	std::cout << "引数２つのmyFuncが呼ばれました。引数は " << a << " " << b << std::endl;
}

int main(){
	myFunc(1);
	myFunc(2, 3);

	return 0;
}
```


## 演習問題(コンソール)

1. 引数で受け取った値の2乗を返す関数mySquare()を作成せよ。mySquare()をint,float,double型の3通りに対応できるようオーバーロードしなさい。


## コンストラクタ

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

class Vector2{
public:
	int x;
	int y;
	
	Vector2(){
		std::cout << "引数なしのコンストラクタが呼ばれました" << std::endl;
		x = 0;
		y = 0;
	}
	
	Vector2(int _x, int _y){
		std::cout << "引数ありのコンストラクタが呼ばれました" << std::endl;
		x = _x;
		y = _y;
	}
};

int main(){

    Vector2 obj1(1, 2);
    std::cout << obj1.x << " " << obj1.y << std::endl;
    
    Vector2 obj2;
    std::cout << obj2.x << " " << obj2.y << std::endl;
    
    return 0;
}
```

## デストラクタ

オブジェクトが破棄されるときにデストラクタが呼ばれる。

>デストラクタの書き方。~(チルダ）をつける

```cpp
~クラスの名前(){
    処理...
}
```

>メイン関数を抜ける時オブジェクトが破棄されるのでデストラクタが呼ばれる。

```cpp
#include <iostream>

class MyClass{
public:
	~MyClass(){
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};

int main(){
	std::cout << "メイン関数に入りました" << std::endl;

	MyClass obj;

	std::cout << "メイン関数を抜けました" << std::endl;

	return 0;
}
```


## 演習問題(コンソール)

1. 以下の様なクラスVector2を作った。コンストラクタとデストラクタを作れ。  
コンストラクタ・デストラクタが呼ばれたら、"～が呼ばれました"と出力するようにせよ。コンストラクタは引数有りのものと引数なし（引数なしの時はx=0,y=0)のものを作ること。  
コンストラクタの初期化の部分は今回紹介した形式で書くこと。

```cpp
class Vector2{
	public:
		int x, y;

		//以下にコンストラクタとデストラクタ書く
}
```


##  Tips : インスタンスの作成と同時に関数を呼ぶ例

以下の例では、色を表すMyColorクラス、円を表すMyCircleクラスを用意し、インスタンスを作成しそのまま関数の引数に入れる例と、インスタンスの作成と同時に関数を呼ぶ例を示している。このように、C++はCに比べ、エレガントな表記が可能になる。  

```cpp
#include <iostream>

// 色を表すクラス (赤成分,緑成分,青成分):(r,g,b)
class MyColor {
public:
	int r, g, b;

	MyColor(int _r, int _g, int _b) :
		r(_r),
		g(_g),
		b(_b)
	{
	}
};

// 円を表すクラス 座標:(x,y)、半径:r
class MyCircle {
public:
	int x, y, r;

	MyCircle(int _x, int _y, int _r) :
		x(_x),
		y(_y),
		r(_r)
	{
	}

	// 自分の情報と、引数にとったMyColorの情報を出力する関数
	void showSelfAndColor(const MyColor& color) {
		std::cout << "Circle:(x, y, r) = (" << x << "," << y << "," << r << ")"
			<< " Color:(r, g, b) = (" << color.r << "," << color.g << "," << color.b << ")" << std::endl;
		std::cout << std::endl;
	}
};


int main() {

	// MyCircleのインスタンスがmyCircleA変数に、MyColorのインスタンスがmyColorA変数に入り、それをshowSelfAndColorで表示する
	MyCircle myCircleA(10, 10, 5);
	MyColor myColorA(70, 80, 90);
	myCircleA.showSelfAndColor(myColorA);

	// MyCircleのインスタンスがmyCircleB変数に入り、MyColorのインスタンスは生成とともにshowSelfAndColorの引数となり表示される
	MyCircle myCircleB(20, 20, 6);
	myCircleB.showSelfAndColor(MyColor(100, 110, 120));

	// MyCircleのインスタンスの生成と同時にshowSelfAndColor関数を呼ぶ。
	// またMyColorのインスタンスも生成とともにshowSelfAndColorの引数となり表示される
	MyCircle(30, 30, 7).showSelfAndColor(MyColor(200, 210, 220));

	return 0;
}
```


##  Tips : emplace_back

vectorに要素を追加する関数は```push_back```を紹介したが、コピーが発生するため非効率なケースがある。そこで、```emplace_back```を使うと、コピーが発生しなくなる。使い方は```push_back```と全く同じである。今後は```emplace_back```を用いる。  

```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
	int a;
	MyClass(int _a) : a(_a) {}
};


int main() {
	std::vector<MyClass> vec;
	vec.emplace_back(MyClass(5));

	return 0;
}
```

##  Tips : constメンバ関数

constメンバ関数を使うと、メンバ変数を変更できないメンバ関数を作ることができる。これを用いることで、誤ってメンバを変更することを防ぐことが出来、また多人数開発の際にメンバ変数を変更していないことを明示できるので，積極的に使うべきである。  

```cpp
#include <iostream>

class MyClass {
public:
	int a;
	MyClass(int _a);
	void func() const;
};


MyClass::MyClass(int _a) {
}

void MyClass::func() const {
	// コメントを外すとメンバ変数を変更してしまうのでコンパイルエラー
	// a = 100;
}


int main() {

	return 0;
}
```
