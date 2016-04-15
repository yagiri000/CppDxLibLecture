#C++講座資料 vol_8

##newとdelete

newを使うと、プログラムの実行中にメモリを確保し、オブジェクトを生成できる。
newすると生成したオブジェクトへのポインタが返ってくる。生成したオブジェクトを見失わないように、ポインタを格納する変数を用意する必要がある。

```cpp
#include <iostream>

class myclass{
public:
	int x;

	myclass(int xx):
	x(xx)
	{

	}

};

int main(){

	myclass* ptr = new myclass(32);
	
	std::cout << "myclassのxの値 : " << ptr->x << std::endl;
	
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

int main(){
	std::cout << "メイン関数に入りました" << std::endl;

	myclass* ptr = new myclass(12);
	
	std::cout << "myclassのxの値 : " << ptr->x << std::endl;
	
	delete ptr;

	std::cout << "メイン関数を抜けました" << std::endl;

	return 0;
}
```

##演習問題

1. 以下のようなクラスを定義した。myclassへのポインタのvectorを用意し、適当な値のa(0~10ぐらい)を持ったデータ10個をnewで生成・格納し、表示した後にaが5以下の要素を削除せよ。  
>ヒント：vectorの要素のmyclassへのポインタを削除しただけでは動的に確保した領域は解放されていない。  
>現時点ではremove_ifを使うとdeleteを呼べないので、whileやforとeraseを使って削除をすること。  


```cpp
#include <iostream>

class myclass{
public:
	int a;

	myclass(int aa):
		a(aa)
	{
	}
};
```
	

##基底クラスと派生クラス

クラスを継承することで、新しいクラスを定義することが出来る。  
継承元のクラスを基底クラス、継承先のクラスを派生クラスという。  
派生クラスは基底クラスのメンバを持つ。  

下の例の場合derivedクラスがbaseクラスを継承している。

```cpp
#include <iostream>

class base{
public:
	base(int xx):
		x(xx)
	{
	}
	int x;
	void show(){
		std::cout << "x:" << x << std::endl;
	}
};

class derived : public base{
public:
	derived(int xx):
		base(xx)
	{
	}
};


int main(void){

	base obj_b(12);
	obj_b.show();

	derived obj_d(23);
	obj_d.show();

	return 0;
}
```

>書き方

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

##演習問題(DXライブラリ)
（1. 2.…と順番に解いていって下さい。 これまでコードを書いてきたプロジェクトとは別に新しくプロジェクトを作ってください。）

1. enemy型へのポインタを要素に持つvectorを用意し、newを使って敵を複数生成せよ。 

1. 画面外に行った敵を削除せよ。newで動的確保した領域も解放すること。
