#C++講座資料 vol_5

C++にはSTLという便利なライブラリが標準でついている。STLにはコンテナがあり、コンテナには便利な配列やリスト構造などがはじめから用意されている。vectorはコンテナの一種である。

##イテレータ

ポインタを抽象化してstd::vectorや他のコンテナでも似た形で使えるようにしたイテレータというものが存在する。  
ポインタが変数をさすのに対して、イテレータはvectorの要素をさす。  
begin()関数は、配列の先頭へのイテレータを返す関数、end()関数は、配列の最後の要素の次へのイテレータを返す関数。  
下の例では、これらを用いてfor文を回している。

```cpp
#include <iostream>
#include <vector>

int main(){

	std::vector<int> vec;
 
	// 10個の要素を追加していく
	for(int i = 0; i < 10; ++i ){
		vec.push_back(rand()%100);
	}
 
	//イテレータを用いて出力
	for(std::vector<int>::iterator iter =vec.begin(); iter !=vec.end(); ++iter){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	
	
	//begin()関数は、配列の先頭へのイテレータを返す関数
	std::vector<int>::iterator iter2 = vec.begin();
	std::cout << *iter2 << std::endl;

	//イテレータはポインタと同じく+することで指す要素を進められる
	//はじめの要素を指すイテレータを4つ進めたので、5番目の要素が出力される
	iter2 += 4;
	std::cout << *iter2 << std::endl;
	
	return 0;
}
```

std::vector&lt;int&gt;::iteratorは長いので、C++の機能である型推論を使い表記を省略できる。
型名の代わりに、autoと書くことで、コンパイラが型を推測してくれる。

```cpp
#include <iostream>
#include <vector>

int main(){

	std::vector<int> vec;
 
	// 10個の要素を追加していく
	for(int i = 0; i < 10; ++i ){
		vec.push_back(i);
	}
 
	//イテレータを用いて出力
	for(auto iter =vec.begin(); iter !=vec.end(); ++iter){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
```

##クラスのvectorのイテレータ
myclassにxという要素があったとする。「myclassのvectorのイテレータ」からそれが指すmyclassのxにアクセスするには、  
イテレータをiterとすると、下のように書けばよい。  

```cpp
iter->x
```

>pointクラスのvectorへのイテレータを使ってpointクラスのx, yを出力

```cpp
#include <iostream>
#include <vector>

class point{
public:
	int x;
	int y;

	point(int xx, int yy) :
		x(xx),
		y(yy)
	{
	}
};

int main(){

	std::vector<point> vec;

	//適当な値のpointを5個入れる
	for (int i = 0; i < 5; i++){
		vec.push_back(point(rand() % 100, rand() % 100));
	}
	
	//出力
	for (auto iter = vec.begin(); iter != vec.end(); ++iter){
		std::cout << iter->x << " " << iter->y << std::endl;
	}

	return 0;
}
```

##vectorの要素の削除

erase関数で要素を削除できる。引数には削除する要素のイテレータを入れる。

```cpp
#include <iostream>
#include <vector>

int main(){

	std::vector<int> vec;//int型の動的配列
 
	// 10個の要素を追加していく
	for(int i = 0; i < 10; i++ ){
		vec.push_back(i);
	}
 
	//イテレータを用いて出力
	for(auto iter = vec.begin(); iter != vec.end(); ++iter){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	
	
	std::cout << "現在のサイズ : " << vec.size() << std::endl;
	
	//4つめの要素の消去
	vec.erase(vec.begin() + 3);

	//イテレータを用いて出力
	for(auto iter =vec.begin(); iter !=vec.end(); ++iter){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	
	std::cout << "現在のサイズ : " << vec.size() << std::endl;
	
	return 0;
}
```


##条件にあった要素の削除
条件にあった複数の要素を削除するには以下のようにする。わりとトリッキー。  
（削除用の関数、remove_ifも存在するが、難しめなので後に紹介する。）  
vectorの要素を削除すると削除した要素を指していたイテレータが迷子になってしまう。erase関数を使って削除をすると、返り値として削除した要素の次の要素へのイテレータが返ってくるので、それをループ用のイテレータに入れる。

```cpp
#include <iostream>
#include <vector>

int main(){

	std::vector<int> vec;//int型の動的配列
 
	// 10個の要素を追加していく
	for(int i = 0; i < 10; i++ ){
		vec.push_back(i);
	}
 
	//出力
	for(auto iter =vec.begin(); iter !=vec.end(); ++iter){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	
	std::cout << "現在のサイズ : " << vec.size() << std::endl << std::endl;
	
	//要素の消去（偶数を消去）
	auto it = vec.begin();
	while(it != vec.end()){
		if(*it % 2 == 0){//偶数だったら
			std::cout << *it << "を消去" << std::endl;
			//eraseの返り値をitで受ける（返り値は削除したものの次につながっていた要素へのイテレータ）
			it = vec.erase(it);
		}else{
			it++;
		}
	}
	std::cout << std::endl;

	//出力
	for(auto iter =vec.begin(); iter !=vec.end(); ++iter){
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	
	std::cout << "現在のサイズ : " << vec.size() << std::endl << std::endl;
	
	return 0;
}
```

##演習問題

1. 以下のようなクラスを用意した。myclassのvectorを作り、適当なa,bの値(0~100ぐらい)をもつデータを10個ほど格納し、表示せよ。  


1. aがbより小さいデータを削除し、再度表示せよ。  

```cpp
#include <iostream>

class myclass{
public:
	int a;
	int b;

	myclass(int aa, int bb):
		a(aa),
		b(bb)
	{
	}
};
```


##演習問題(DXライブラリ)
（1. 2.…と順番に解いていって下さい。 これまでコードを書いてきたプロジェクトとは別に新しくプロジェクトを作ってください。）

1. これまでvectorを配列表記で描いてきた部分を、イテレータを用いて書き直せ。

1. 前回の課題で、y座標が600を超えた敵(下の方の画面外に出た敵)を削除するようにせよ。  

1. 画面外に出た敵を削除するようにせよ。


