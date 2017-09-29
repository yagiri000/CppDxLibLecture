#　C++DxLib講座資料

## 基底クラスへのポインタ

基底クラスへのポインタには、派生クラスのポインタを入れることが出来る。

```cpp
#include <iostream>

class Base{
public:
	int x;

	Base(int _x):
		x(_x)
	{
	}

	void show(){
		std::cout << "show関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class Derived : public Base{
public:
	Derived(int _x) : Base(_x)
	{
	}
	
};

int main(){

	Base obj_b(100);
	Derived obj_d(200);

	obj_b.show();
	obj_d.show();

	std::cout << std::endl;

	Base *ptr1 = &obj_b;
	Base *ptr2 = &obj_d; //基底クラスへのポインタに派生クラスのポインタを入れられる
	
	ptr1->show();
	ptr2->show();
	
	std::cout << std::endl;

	return 0;
}
```


## 仮想関数

基底クラスでvirtualをつけ仮想関数を作り、派生クラスでその関数をオーバーライドすることで、派生クラスを指している基底クラスへのポインタから、派生クラスで再定義された関数を呼び出すことが出来るようになる。  
以下は、show関数をオーバーライドしている例。メンバ関数の前にvirtualをつけることで仮想関数を定義できる。また、派生クラスでは、override指定子をつけてオーバーライドを明示しながらshow関数をオーバーライドしている。  


```cpp
#include <iostream>

class Base{
public:
	int x;

	Base(int _x):
		x(_x)
	{

	}

	virtual void show(){
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class Derived : public Base{
public:
	Derived(int _x) : 
		Base(_x)
	{
	}

	void show() override {
		std::cout << "派生クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

int main(){

	Base obj_b(100);
	Derived obj_d(200);

	obj_b.show();
	obj_d.show();

	std::cout << std::endl;

	Base *ptr1 = &obj_b;
	Base *ptr2 = &obj_d; // ptr2は、派生クラスを指している基底クラスへのポインタ
	
	ptr1->show();
	ptr2->show();
	
	std::cout << std::endl;

	return 0;
}
```

> newで動的に領域を確保したバージョン（そんなに変わりはない）

```cpp
#include <iostream>

class Base{
public:
	int x;

	Base(int _x):
		x(_x)
	{
	}

	virtual void show(){
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class Derived : public Base{
public:
	Derived(int _x) : 
		Base(_x)
	{
	}

	void show(){
		std::cout << "派生クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};


int main(){

	Base *ptr1 = new Base(100);
	Base *ptr2 = new Derived(200);
	
	ptr1->show();
	ptr2->show();
	
	std::cout << std::endl;

	return 0;
}
```

> newで動的に領域を確保したバージョン、その２。派生クラスが複数になっただけ。

```cpp
#include <iostream>

class IEnemy {
public:
	int x;

	//コンストラクタ
	IEnemy(int _x) :
		x(_x)
	{
	}

	virtual void show() {
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class EnemyA : public IEnemy {
public:

	EnemyA(int _x) :
		IEnemy(_x)
	{
	}

	void show() override {
		std::cout << "EnemyAクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyB : public IEnemy {
public:

	EnemyB(int _x) : 
		IEnemy(_x) 
	{
	}

	void show() override {
		std::cout << "EnemyBクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyC : public IEnemy {
public:

	EnemyC(int _x) :
		IEnemy(_x) 
	{
	}

	void show() override {
		std::cout << "EnemyCクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};



int main() {

	IEnemy *ptr1 = new EnemyA(100);
	IEnemy *ptr2 = new EnemyB(200);
	IEnemy *ptr3 = new EnemyC(320);

	ptr1->show();
	ptr2->show();
	ptr3->show();

	return 0;
}
```

## 継承によるポリモーフィズム

例えばシューティングで敵A,敵B,敵Cを作りたいとする。もし、敵A,敵B,敵Cの配列をそれぞれ作って管理しようとすると大変だし、敵が一種類増えるたびに新しい配列を作らなければならない。
下のようにEnemyの基底クラスIEnemyを定義し、それを継承すれば、派生クラスを一つの配列で扱うことが可能になる。

```cpp
#include <iostream>
#include <vector>

class IEnemy {
public:
	int x;

	//コンストラクタ
	IEnemy(int _x) :
		x(_x)
	{
	}

	virtual void show() {
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class EnemyA : public IEnemy {
public:

	EnemyA(int _x) : 
		IEnemy(_x) 
	{
	}

	void show() override {
		std::cout << "EnemyAクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyB : public IEnemy {
public:

	EnemyB(int _x) :
		IEnemy(_x) 
	{
	}

	void show() override {
		std::cout << "EnemyBクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyC : public IEnemy {
public:

	EnemyC(int _x) :
		IEnemy(_x) 
	{
	}

	void show() override {
		std::cout << "EnemyCクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};



int main() {
	std::vector<IEnemy*> vec;

	vec.emplace_back(new EnemyA(100));
	vec.emplace_back(new EnemyB(200));
	vec.emplace_back(new EnemyC(320));

	//違うクラスなのに、同じ配列で扱えた！！！！！
	for (const auto& enemy : vec) {
		enemy->show();
	}

	return 0;
}
```

##  純粋仮想関数

純粋仮想関数を作ると、そのクラスはインスタンス化出来なくなる。
上の例では敵A,B,Cの基底クラスにIEnemyが定義されているが、このようなクラスをインターフェイスを定義するクラスという。
純粋仮想関数はインターフェイスを定義するクラスを作るときに使い、誤ってインターフェイスを定義するクラスを生成してしまうのを防げる。

```cpp
#include <iostream>

class Base {
public:
	double x;

	Base(int _x) :
		x(_x)
	{
	}

	virtual void show() = 0;
};

class Derived : public Base {
public:
	Derived(int _x) : 
		Base(_x)
	{
	}

	void show() {
		std::cout << "派生クラスのshowが呼ばれました。 xは:" << x << std::endl;
	}
};

int main() {
	Base *ptr1 = new Derived(100);
	ptr1->show();

	//コメントを外すと純粋仮想関数をもつクラスをインスタンス化してしまうのでコンパイルエラー
	//Base b(100);
	//Base *ptr2 = new Base(100);

	return 0;
}
```

> 純粋仮想関数　書き方

virtual 返り値の型 関数名() = 0;
例：virtual void show() = 0;


## 演習問題(コンソール)

1. 以下の様なクラスを作った。Dog,Yojoを参考に、IAnimalクラスを継承したクラスをもう1つ作れ。

1. IAnimal型へのポインタを要素に持つvectorにnewで動的確保したIAnimalの派生クラスへのポインタを適当に複数入れた後、すべてのインスタンスのtalk関数を呼び出せ。  

1. IAnimalのtalk関数を純粋仮想関数にせよ。  

```cpp
class IAnimal {
public:
	double weight;//重さ

	IAnimal(int w) :
		weight(w) 
	{

	}

	virtual void talk() {
		std::cout << "基底クラスのtalk関数が呼ばれました。 重さは:" << weight << std::endl;
	}
};

class Dog : public IAnimal {
public:
	Dog(int w) : 
		IAnimal(w) 
	{
	}

	void talk() override {
		std::cout << "わんわん　重さは:" << weight << std::endl;
	}
};

class Yojo : public IAnimal {
public:
	Yojo(int w) : 
		IAnimal(w) 
	{
	}

	void talk() override {
		std::cout << "ふぇぇ…　重さは:" << weight << std::endl;
	}
};
```

##  演習問題(DxLib)

* 前回のプログラムを書き換え、継承によるポリモーフィズムを用いて、敵を数種類作れ。


##  ヒント : 宣言と定義を分ける場合のoverrideの書き方  
以下の例はDerivedクラス内でshow関数をオーバーライドした例。override指定子はクラス内の関数宣言(.hのほう)にはつけるが、関数定義(cppのほう)にはつけない。

>  Derived.h

```cpp
class Derived : public IBase {
public:
	void show() override;
};
```

>  Derived.cpp

```cpp
void Derived::show() {
	std::cout << "派生クラスのshow関数が呼ばれました。" << std::endl;
}
```


##  Tips : override指定子  
実は、override指定子がなくてもオーバーライドすることはできる。しかし、override指定子を用いてオーバーライドを明示することで、コンパイラにoverrideしていることを明示し、ミスを防ぐことができる。  
以下は、show関数を派生クラスでオーバーライドするつもりだったが、showaaとミスタイプしてしまった例。override指定子を用いてoverrideを明示しているが、showaaという名前の仮想関数はないので、コンパイルしようとするとコンパイルエラーになり、オーバーライドしそびれていることに早い段階で気づけるようになっている。  
*※以下の例はコンパイルできない！！*

```cpp
// このソースコードはコンパイル不可
#include <iostream>

class Base {
public:
	virtual void show() {
		std::cout << "基底クラスのshow関数が呼ばれました。" << std::endl;
	}
};

class Derived : public Base {
public:
	// 本当はshowとタイプするつもりだったが、showaとミスタイプしてしまった例。コンパイルできない。
	void showaa() override {
		std::cout << "派生クラスのshow関数が呼ばれました。" << std::endl;
	}
};

int main() {
	Base base;
	Derived derived;

	base.show();
	derived.show();

	return 0;
}
```


## Tips :　ポリモーフィズム用基底クラスには仮想デストラクタが必要

以下の例では、Baseを継承したDerivedクラスを作り、Derivedをnewした後、そのポインタをBaseへのポインタに入れ、その後deleteしている。また、基底クラスBaseで仮想デストラクタを定義、派生クラスDerivedでデストラクタをオーバーライドし定義している。  
Derivedクラスを指すBaseクラスのポインタを解放した際、Baseクラスに仮想デストラクタがないと、Baseクラスとしての領域のみ解放されてしまい、Derivedクラスの領域が解放されない。よって、ポリモーフィズムのための基底クラスには仮想デストラクタの宣言が必要である。

```cpp
#include <iostream>
1
class Base {
public:
	int x;
	
	Base(int _x) :
		x(_x)
	{
	}

	// 仮想デストラクタを定義
	virtual ~Base() {
		std::cout << "仮想デストラクタ~Baseが呼ばれました。" << std::endl;
	};
};

class Derived : public Base {
public:
	Derived(int _x) :
		Base(_x)
	{
	}

	// デストラクタをオーバーライドし定義
	~Derived() {
		std::cout << "デストラクタ~Derivedが呼ばれました。" << std::endl;
	};
};


int main() {

	Base* ptr = new Derived(10);
	delete ptr;

	return 0;
}
```

デストラクタの中身が特にない場合は、以下のようにdefaultをつけてデストラクタの中身の生成をコンパイラに任せることができる。また、派生クラスのデストラクタは自動生成されるもので問題ないので、書かなくてもよい。

```cpp
#include <iostream>

class Base {
public:
	int x;
	
	Base(int _x) :
		x(_x)
	{
	}

	// 仮想デストラクタを定義
	virtual ~Base() = default;
};

class Derived : public Base {
public:
	Derived(int _x) :
		Base(_x)
	{
	}

	// デストラクタをオーバーライドし定義
	~Derived() = default;
};


int main() {

	Base* ptr = new Derived(10);
	delete ptr;

	return 0;
}
```
