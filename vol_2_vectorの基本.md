#C++講座資料 vol_2

今回は動的配列vectorの基本について学ぶ。
演習では、DXライブラリを用いて複数の敵を生成する。


##vectorの基本的な使い方

C言語の配列は固定長だったが、C++には必要に応じて自動的にサイズを変更してくれる配列、vectorがある。
vectorの要素には配列と同じように[]でアクセス出来る。
vectorを使うときはvectorヘッダをインクルードする。

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
    for(int i = 0; i < vec.size(); i++ ){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "現在のサイズ : " << vec.size() << std::endl;
    
    return 0;

}
```

>書き方

```
std::vector<動的配列の中に入れる型> 動的配列の変数名;

例：std::vector<double> ary1;
```

>追加の仕方  
以下の例では、point(x,y)でpointの実体をつくり、push\_backによってvectorの末尾に追加している。

```
動的配列名.push_back(追加するデータ);

例：point型の動的配列aryに point(x,y)を入れるとしたら
ary.push_back(point(x,y))
```

>配列のサイズ取得(返り値はunsigned int型)

```
動的配列名.size()
```

>クラスのvector例

```cpp
#include <iostream>
#include <vector>

class myclass{
public:
	int x;

	myclass(int xx){
		x = xx;
	}
};


int main(void){

	std::vector<myclass> vec;

	//要素を追加
	for(int i = 0; i < 10; i++){
		vec.push_back(myclass(rand()%10));
	}

	//要素myclassのxを表示
	for(int i = 0; i < (int)vec.size(); i++){
		std::cout << vec[i].x << " ";
	}

	std::cout << std::endl;//改行

	return 0;
}
```

##演習問題
1. int型のvectorを用意し、ランダムに0~9の数を10個入れて、すべて表示せよ。  
上記のvectorの中で5以下の要素を表示せよ。
>ヒント：ランダムな0~9の数を生成するにはrand()%10とすればよい。
（今回はsrandとかは呼ばなくていいです。より性能の高い乱数生成器が入っているrandomヘッダーに関しては後でやります。）

1. 以下の様なクラスmyclassを用意した。myclassのvectorを用意し、vectorにmyclassを10個追加し、すべての要素のshow()関数を呼び出せ。xの値はランダムな数でよい。

		class myclass{
		public:
			int x;

			myclass(int xx){
				x = xx;
			}

			void show(){
				std::cout << "xは：" << x << std::endl;
			}
		};


1. 以下の様なpointクラスを作った。  
pointクラスのvectorを用意し、rand()などを使って適当な座標を10個格納し、表示せよ。  

		class point{
		public:
			int x;
			int y;
			
			point(int xx, int yy){
				x = xx;
				y = yy;
			}
		};

##演習問題(DXライブラリ)
（1. 2.…と順番に解いていって下さい。 これまでコードを書いてきたプロジェクトとは別に新しくプロジェクトを作ってください。）

1. 以下の様なplayerクラスとenemyクラスを用意した。playerクラスとenemyクラスのインスタンスを作り、動作を確認せよ。

	>playerクラス

			class player{
			public:
				double x, y;
				double movev;

				player(){
					x = 400;
					y = 500;
					movev = 3;
				}

				void update(){
					if(CheckHitKey(KEY_INPUT_RIGHT) == 1){
						x += movev;
					}
					if(CheckHitKey(KEY_INPUT_LEFT) == 1){
						x -= movev;
					}
					if(CheckHitKey(KEY_INPUT_UP) == 1){
						y -= movev;
					}
					if(CheckHitKey(KEY_INPUT_DOWN) == 1){
						y += movev;
					}
				}

				void draw(){
					DrawCircle(x, y, 10, GetColor(0, 0, 255), 1);
				}

			};


	>enemyクラス

			class enemy{
			public:
				double x, y, vx, vy;
				enemy(double xx, double yy){
					x = xx;
					y = yy;
					vx = 0;
					vy = 1.0;
				}

				void update(){
					x += vx;
					y += vy;
				}

				void draw(){
					DrawCircle(x, y, 24, GetColor(255, 0, 0), 1);
				}

			};


1. player.hとenemy.hを作り、playerクラスとenemyクラスをファイル分けせよ。

1. enemyのvectorを作り、enemyが複数出るようにせよ。

1. Zキーが押されたらランダムな座標に敵が出るようにせよ。

1. 現在、メインループ内でenemyのvectorをfor文で回していると思う。  
メインループ内はできるだけすっきりさせたい。そこで、enemyのvectorをメンバに持ち、updateを呼ぶとメンバのenemyのupdateをすべて呼ぶenemymanagerクラスを作り、メインループ内ではenemymanagerのupdateを呼ぶのみでenemyすべてが更新され、enemymanagerのdrawを呼ぶだけですべての敵が描画されるようにする。  
enemymanagerクラスを作り、敵を管理せよ。  

		class enemymanager{
		public:
			//ここにenemyの動的配列


			void update(){
				//ここを実装
				//配列内のenemyのupdateを呼ぶ
			}

			void draw(){
				//ここを実装
				//配列内のenemyのdrawを呼ぶ
			}

			void addenemy(double x, double y){
				//ここを実装
				//指定された座標に敵を生成
			}

		};

1. enemy.hとは別にenemymanager.hを作り、ファイル分けをせよ。

1. 現在の敵の数を画面左上に表示せよ。ヒント：vectorのsize関数

