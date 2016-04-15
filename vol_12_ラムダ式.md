#C++講座資料 vol_12

今回はC++の中でも特に書き方が変態的なラムダ式を扱う。

##ラムダ式

remove\_ifを使う時、大きなプログラムになると削除するかを判定する関数の定義と使う部分が離れてしまう。  そこでC++11からはラムダ式というものが導入された。 例えば2で割り切れるかを返す関数オブジェクトを生成する場合  

```cpp
#include <iostream>

int main(){
    
    //2で割り切れるかどうかを返す関数オブジェクトを生成
    auto isMultiple2 = [](int num){return (num % 2) == 0;};
      
    std::cout << isMultiple2(3) << std::endl;
    std::cout << isMultiple2(4) << std::endl;
      
    return 0;
    
}
```


上のコードの

```cpp
[](int num){return (num % 2) == 0;}
```

の部分がラムダ式だ。 ラムダ式の型はautoで推論させている。(仕様上未定義なため)


ラムダ式の書き方

```cpp
[](引数){処理};
```

ところで返り値の型を指定していないことに気づいただろうか? これは多くの場合(ラムダ式内部でforを使うとかしない限り)指定しなくてよいものだ。
ラムダ式の返り値を明示的に指定する場合は

```cpp
[](引数)->返り値の型{
	処理
};
```

のように()のあとに「->(返り値の型)」という形式にする。


##ラムダ式とremove_if

ラムダ式を用いると、remove_if関数の近くに条件を判定する関数を書くことが出来る。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	std::vector<int> vec;//int型の動的配列

	for(int i = 0; i < 10; i++){
		vec.push_back(i);
	}

	//表示
	for(auto i = vec.begin(); i < vec.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	
	//3の倍数かどうかを返す関数
	auto isMulThree = 
		[](int x){
			return (x % 3) == 0;
		};
	
	//vecの中から3の倍数を後ろに詰める
	auto rmviter = std::remove_if(vec.begin(), vec.end(), isMulThree);

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



remove_if関数の中に条件を判定する関数を直接書くことが出来る。

下の例では、第三引数に直接ラムダ式を書いている。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	std::vector<int> vec;//int型の動的配列

	for(int i = 0; i < 10; i++){
		vec.push_back(i);
	}

	//表示
	for(auto i = vec.begin(); i < vec.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	
	
	
	//vecの中から3の倍数を後ろに詰める
	auto rmviter = std::remove_if(vec.begin(),vec.end(),
		[](int x){
			return (x % 3) == 0;
		}
	);

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

##演習問題

1. 受け取った値を2倍にして返す関数をラムダ式を用いて作成せよ。

1. int型のvectorに0から9を入れ、remove_ifとラムダ式を用いて2の倍数を削除せよ。

1. 以下のようなクラスmyclassを定義した。myclassへのスマートポインタのvectorを用意し、適当な値のa(0~10ぐらい)を持ったデータを10個格納し、aが5以下の要素をremove_ifを用いて削除せよ。  
myclassへのスマートポインタのvectorとは、`std:vector<std::shared_ptr<myclass>> vec`である。  



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

##演習問題(DXライブラリ)
（1. 2.…と順番に解いていって下さい。 これまでコードを書いてきたプロジェクトとは別に新しくプロジェクトを作ってください。）

1. enemyのクラスへのスマートポインタを要素に持つvectorを用意し、敵を複数生成せよ。  
領域確保はnewではなく、std::make_sharedを使うこと。要素の削除にはalgorithmのremove\_ifを使い、その条件の指定にはラムダ式を使用せよ。  
