#C++講座資料 vol_6

##参照を返す関数  
以下の例では、int型の変数hogeを用意し、hogeに対し複数の方法でアクセスしている。  
hogeは日本では特に意味のない名前を表す。  

```cpp
#include <iostream>

//int型の変数を用意
int hoge;

//hogeのポインタを返す関数(ptrはpointerの略)
int* getptr(){
	return &hoge;
}

//hogeの参照を返す関数(refはreferenceの略)
int& getref(){
	return hoge;
}

//hogeの値を返す関数
int getnum(){
	return hoge;
}

int main(void){

	hoge = 10;
	std::cout << hoge << std::endl;

	*(getptr()) = 20;
	std::cout << hoge << std::endl;

	getref() = 30;
	std::cout << hoge << std::endl;

	//getnumはhogeの値を返す関数なので、値を代入できない。コメントアウトを外すとコンパイルエラー。
	//getnum() = 40;

	return 0;
}
```



##シングルトン

シングルトンは、インスタンス（実体）が一つしか存在しないことが保証される。また、どのオブジェクトからもアクセスできる。  
扱い次第では、グローバル変数のように機能させることもできる。どのオブジェクトからもアクセスできるのを活かして、どのキーが押されているか保持するクラスとして使ったり、グラフィック、効果音を管理するクラスとして機能させることも出来る。  
以下の例では、get()関数が初めて呼ばれた時にシングルトンクラスの実体ができる。また、main関数の前にget()関数を呼ぶとエラーが出る。  
コンストラクタやコピーコンストラクタ、イコール演算子をprivateに置くことで、それらを外部から呼べないようにして、クラス内でしか実体を作れないようにしている。  
get()関数内にmysingletonクラスの実体が存在し、get()関数はその実体への参照を返すので、get()関数を通してmysingletonクラスの実体にアクセスすることができる。

```cpp
#include <iostream>

class mysingleton{
private:
mysingleton(){//コンストラクタをprivateに置き、クラス外で生成するのを禁止
	x = 30;	
}

mysingleton(const mysingleton& r){}//コピーを禁止
mysingleton& operator=(const mysingleton& r){} //代入を禁止

public:
static mysingleton& get(){
	static mysingleton inst;
	return inst;
}

int x;

void func(){
	std::cout << "クラス内の関数が呼ばれました" << std::endl;
}
};

int main(){

//get関数を通してアクセス可能
std::cout << mysingleton::get().x << std::endl;
mysingleton::get().func();

//直接アクセスするのは無理。コメントを外すとコンパイルエラー
//std::cout << mysingleton::x << std::endl;

return 0;
}
```

##演習

1. シングルトンのクラスmysingletonを作り、以下の関数を実装せよ。必要な変数があれば、自分で考えて実装すること。
* showhoge() : "hoge"と出力する関数
* randint(int num)　: 0~(引数に入力された数) のうちランダムな数を返す関数
* calledfuncnum() : シングルトン内の関数が呼ばれた回数を返す関数

##演習(DXライブラリ)
（1. 2.…と順番に解いていって下さい。 これまでコードを書いてきたプロジェクトとは別に新しくプロジェクトを作ってください。）

1. シングルトンを用いて、キーの状態、マウスの座標を取得できるInputクラスを作成せよ。

・必要なメンバ変数、メンバ関数  
keystate[]　： 各キーが何フレーム押されているかが入っている配列  
buf[]　： 各キーが押されているかを入れる配列（keystate更新のために使う）  
mousex,mousey　：　マウス座標  
update()　：　keystate配列とmousex,mouseyを更新する関数。メインループ内で毎フレーム呼ぶ必要がある。  


1. enemyクラス内にint型のmode変数を作り、mode変数によって敵が多様な動きをするようにせよ。  
(mode==1なら自機に直進、mode==2ならsin軌道、mode==3なら出た位置で円運動…など)  
modeの値は敵の生成時にGetRand()などで適当に決めて良い。addenemy関数の引数で指定できても良い。    
ちなみに、GetRand(3)とすると、0,1,2,3のどれかが返ってくる。0,1,2でないことに注意。

1. modeによって敵の色が変わるようにせよ。

1. modeをenum型にせよ。クラス内で定義されたenumは、クラス外部からは(クラス名)::(要素の名前)で	enumを指定できる。


##ヒント：enum型    
クラス内でenumを定義し使用する例。  
hogeクラスを用意し、enumのpiyoである変数modeを用意し、クラス外部からmodeを変更して出力していっている。
  
```cpp
#include <iostream>

class hoge{
public:
	enum piyo{
		aaa,
		bbb,
		ccc,
	};

	piyo mode;

	//コンストラクタ　modeの初期値をaaaに
	hoge(){
		mode = aaa;
	}

	//modeをセットする関数
	void setmode(piyo p){
		mode = p;
	}
};

int main(void){
	hoge inst;

	//出力。内部的には整数（0から始まる）
	std::cout << inst.mode << std::endl;

	//クラス外からアクセスするには「クラス名::項目」とする。
	inst.mode = hoge::bbb;
	//出力
	std::cout << inst.mode << std::endl;

	//関数を用いてセット
	inst.setmode(hoge::ccc);
	std::cout << inst.mode << std::endl;

	return 0;
}
```