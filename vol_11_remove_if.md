#C++講座資料 vol_11

vectorはコンテナの一種である。コンテナに対してソートや削除を行うアルゴリズムというものがある。 （一般に言うアルゴリズムではない）  
今回はアルゴリズムに関して扱う。

##ソート std::sort

std::sortを使うと、コンテナの中身を小さい順にソートすることができる。このソート関数の中身はC++の中の人が作ったものなので、とても高速である。  
アルゴリズムを使うには、algorithmヘッダーをインクルードする。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
	std::vector<int> vec;
    
	//適当な数を10個入れる
	for(int i = 0; i < 10; i++){
		vec.push_back(rand()%30);
	}

	//表示
	for(auto i = vec.begin(); i < vec.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	//ソート
	std::sort(vec.begin(), vec.end());

	//表示
	for(auto i = vec.begin(); i < vec.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	return 0;
}
```

##要素を削除 std::remove_if

remove_ifは条件にあった要素を削除する。  
正確には、条件にあった要素を、vectorの後ろに配置しなおし、削除したように見せかけた後のvectorの最後のイテレータを返す。  つまり、remove_if関数を呼んだだけでは要素は削除されておらず、その後にerase関数を呼ぶ必要がある。  


//remove_ifを実行し、条件にあった要素を後ろに詰める。
auto rmviter = std::remove_if(vec.begin(),vec.end(), 関数ポインタ);

//後ろの方に詰められた要素を削除
vec.erase( rmviter, vec.end() );


remove\_ifの第一引数には削除するかを判定する範囲の先頭、第二引数には終端を書く。
remove\_ifの第三引数には削除の条件を返す関数の名前を書く。（正確には関数ポインタ）

>3の倍数を削除する例

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

//3の倍数かどうかをたしかめて返す叙述関数
bool isMultipleThree(int x){
	return (x%3) == 0;
}

int main(){

	std::vector<int> vec;//int型の動的配列

	//0から数を入れる
	for(int i = 0; i < 10; i++){
		vec.push_back(i);
	}

	//表示
	for(auto i = vec.begin(); i < vec.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;


	//vecの中から3の倍数を後ろに詰める
	//3の倍数かどうかの判定は3番目のパラメータで渡された関数ポインタで判定
	auto rmviter = std::remove_if(vec.begin(), vec.end(), isMultipleThree);

	//実際に削除
	vec.erase( rmviter, vec.end() );

	//表示
	for(auto i = vec.begin(); i < vec.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	return 0;
}
```

>remove\_ifの第三引数には、remove\_ifが対象にするvectorの中身を引数に取り、bool型(trueかfalse)を返す関数を入れる。以下が例。

```cpp
bool func(配列の要素の型 x){
	return (x%3) == 0;//条件に一致してるか確認してbool型を返す
}
```

##演習問題
1. 以下のようなクラスを定義した。myclassのvectorを用意し、適当な値のa(0~10ぐらい)を持ったデータを10個格納し、aが5以下の要素をremove_ifを用いて削除せよ。


```cpp
class myclass{
public:
	int a;

	myclass(int aa):
		a(aa)
	{
	}
};
```