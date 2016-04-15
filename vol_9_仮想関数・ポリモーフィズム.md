#C++講座資料 vol_9

##基底クラスへのポインタ

基底クラスへのポインタには、派生クラスのポインタを入れることが出来る。

```cpp
#include <iostream>

class base{
public:
	int x;

	base(int xx):
		x(xx)
	{
	}

	void show(){
		std::cout << "show関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class derived : public base{
public:
	derived(int xx) : base(xx)
	{
	}
	
};

int main(void){

	base obj_b(100);
	derived obj_d(200);

	obj_b.show();
	obj_d.show();

	std::cout << std::endl;

	base *ptr1 = &obj_b;
	base *ptr2 = &obj_d; //基底クラスへのポインタに派生クラスのポインタを入れられる
	
	ptr1->show();
	ptr2->show();
	
	std::cout << std::endl;

	return 0;
}
```


##仮想関数

基底クラスでvirtualをつけ仮想関数を作り、派生クラスでその関数をオーバーライドすることで、派生クラスを指している基底クラスへのポインタから、派生クラスで再定義された関数を呼び出すことが出来るようになる。  
以下のshow関数のように、クラスの関数の前にvirtualをつけることで仮想関数を定義できる。  


```cpp
#include <iostream>

class base{
public:
	int x;

	base(int xx):
		x(xx)
	{

	}

	virtual void show(){
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class derived : public base{
public:
	derived(int xx) : base(xx)
	{
	}

	void show(){
		std::cout << "派生クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

int main(void){

	base obj_b(100);
	derived obj_d(200);

	obj_b.show();
	obj_d.show();

	std::cout << std::endl;

	base *ptr1 = &obj_b;
	base *ptr2 = &obj_d; // ptr2は、派生クラスを指している基底クラスへのポインタ
	
	ptr1->show();
	ptr2->show();
	
	std::cout << std::endl;

	return 0;
}
```

>newで動的に領域を確保したバージョン（そんなに変わりはない）

```cpp
#include <iostream>

class base{
public:
	int x;

	base(int xx):
		x(xx)
	{
	}

	virtual void show(){
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class derived : public base{
public:
	derived(int xx) : base(xx)
	{
	}

	void show(){
		std::cout << "派生クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};


int main(void){

	base *ptr1 = new base(100);
	base *ptr2 = new derived(200);
	
	ptr1->show();
	ptr2->show();
	
	std::cout << std::endl;

	return 0;
}
```

>newで動的に領域を確保したバージョン、その２。派生クラスが複数になっただけ。

```cpp
#include <iostream>

class I_Enemy{
public:
	int x;
	
	//コンストラクタ
	I_Enemy(int xx):
		x(xx)
	{
	}

	virtual void show(){
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class EnemyA : public I_Enemy{
public:
	
	EnemyA(int xx) : I_Enemy(xx){

	}

	void show(){
		std::cout << "EnemyAクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyB : public I_Enemy{
public:
	
	EnemyB(int xx) : I_Enemy(xx){

	}

	void show(){
		std::cout << "EnemyBクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyC : public I_Enemy{
public:
	
	EnemyC(int xx) : I_Enemy(xx){

	}

	void show(){
		std::cout << "EnemyCクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};



int main(void){

	I_Enemy *ptr1 = new EnemyA(100);
	I_Enemy *ptr2 = new EnemyB(200);
	I_Enemy *ptr3 = new EnemyC(300);
	
	ptr1->show();
	ptr2->show();
	ptr3->show();

	return 0;
}
```

##継承によるポリモーフィズム

例えばシューティングで敵A,敵B,敵Cを作りたいとする。もし、敵A,敵B,敵Cの配列をそれぞれ作って管理しようとすると大変だし、敵が一種類増えるたびに新しい配列を作らなければならない。
下のようにEnemyの基底クラスI_Enemyを定義し、それを継承すれば、派生クラスを一つの配列で扱うことが可能になる。

```cpp
#include <iostream>
#include <vector>

class I_Enemy{
public:
	int x;
	
	//コンストラクタ
	I_Enemy(int xx):
		x(xx)
	{
	}

	virtual void show(){
		std::cout << "基底クラスのshow関数が呼ばれました。　xは:" << x << std::endl;
	}
};

class EnemyA : public I_Enemy{
public:
	
	EnemyA(int xx) : I_Enemy(xx){

	}

	void show(){
		std::cout << "EnemyAクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyB : public I_Enemy{
public:
	
	EnemyB(int xx) : I_Enemy(xx){

	}

	void show(){
		std::cout << "EnemyBクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};


class EnemyC : public I_Enemy{
public:
	
	EnemyC(int xx) : I_Enemy(xx){

	}

	void show(){
		std::cout << "EnemyCクラスのshow関数が呼ばれました。 xは:" << x << std::endl;
	}
};



int main(void){
	std::vector<I_Enemy*> vec;

	vec.push_back(new EnemyA(100));
	vec.push_back(new EnemyB(200));
	vec.push_back(new EnemyC(300));

	//違うクラスなのに、同じ配列で扱えた！！！！！
	for(auto i = vec.begin(); i < vec.end(); ++i){
		(*i)->show();
	}

	return 0;
}
```

##純粋仮想関数

純粋仮想関数を作ると、そのクラスはインスタンス化出来なくなる。
上の例では敵A,B,Cの基底クラスにI_Enemyが定義されているが、このようなクラスをインターフェイスを定義するクラスという。
純粋仮想関数はインターフェイスを定義するクラスを作るときに使い、誤ってインターフェイスを定義するクラスを生成してしまうのを防げる。

```cpp
#include <iostream>

class base{
public:
	double x;

	base(int xx):
		x(xx)
	{
	}

	virtual void show() = 0;
};

class derived : public base{
public:
	derived(int xx): base(xx)
	{
	}

	void show(){
		std::cout << "派生クラスのshowが呼ばれました。 xは:" << x << std::endl;
	}
};

int main(void){
	base *ptr1 = new derived(100);
	ptr1->show();

	//コメントを外すと純粋仮想関数をもつクラスをインスタンス化してしまうのでコンパイルエラー
	//base b(100);
	//base *ptr2 = new base(100);

	return 0;
}
```

>純粋仮想関数　書き方

virtual 返り値の型 関数名() = 0;
例：virtual void show() = 0;


##演習問題

1. 以下の様なクラスを作った。I\_animalクラスを継承したクラスをもう２つ作れ。

1. I\_animal型へのポインタを要素に持つvectorにnewで動的確保したI\_animalの派生クラスへのポインタを適当に複数入れた後、すべてのインスタンスのtalk関数を呼び出せ。  

1. I_animalのtalk関数を純粋仮想関数にせよ。  

```cpp
class I_animal{
public:
	double weight;//重さ

	I_animal(int w) : weight(w){

	}

	virtual void talk(){
		std::cout << "基底クラスのtalk関数が呼ばれました。 重さは:" << weight << std::endl;
	}
};

class dog : public I_animal{
public:
	dog(int w) : I_animal(w){

	}

	void talk(){
		std::cout << "わんわん　重さは:" << weight << std::endl;
	}
};

class yojo : public I_animal{
public:
	yojo(int w) : I_animal(w){

	}

	void talk(){
		std::cout << "ふぇぇ…　重さは:" << weight << std::endl;
	}
};
```

##演習問題(DXライブラリ)

* 継承によるポリモーフィズムを用いて、敵を数種類作れ。


