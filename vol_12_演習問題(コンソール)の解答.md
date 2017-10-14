# 演習問題(コンソール)解答例

以下に演習問題(コンソール)の解答例を示す。  

## vol_1課題1(コンソール)

```cpp
#include <iostream>

int main() {
	int input;
	std::cout << "整数値を入力してください：" << std::endl;
	std::cin >> input;//inputに入力された数値を代入
	std::cout << "入力された値は、" << input << "です。" << std::endl;

	return 0;
}
```


## vol_1課題2(コンソール)

```cpp
#include <iostream>

class Vector3 {
public:
	int x, y, z;

	// コンストラクタ
	Vector3(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	// x, y, zの値を表示
	void show() {
		std::cout << x << "," << y << "," << z << std::endl;
	}

	// x * y * zの値を表示
	void showMultiple() {
		std::cout << x *y* z << std::endl;
	}
};

int main() {
	Vector3 vec3(1, 2, 3);
	vec3.show();
	vec3.showMultiple();

	return 0;
}
```

## vol_3課題1(コンソール)

```cpp
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(rand() % 10);
	}

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < vec.size(); i++) {
		int n = vec[i];
		if (n <= 5) {
			std::cout << n << std::endl;
		}
	}

	return 0;
}
```


## vol_3課題2(コンソール)

```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
	int x;

	MyClass(int _x) :
		x(_x)
	{
	}

	void show() {
		std::cout << "xは：" << x << std::endl;
	}
};

int main() {
	std::vector<MyClass> vec;
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(MyClass(rand() % 100));
	}

	for (int i = 0; i < vec.size(); i++) {
		vec[i].show();
	}

	return 0;
}
```

## vol_3課題3(コンソール)

```cpp
#include <iostream>
#include <vector>

class Point2 {
public:
	int x;
	int y;

	Point2(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

int main() {
	std::vector<Point2> vec;
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(Point2(rand() % 100, rand() % 100));
	}

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i].x << ", " << vec[i].y << std::endl;
	}

	return 0;
}
```

## vol_4課題1(コンソール)

```cpp
#include <iostream>

int mySquare(int x) {
	std::cout << "int型のmySquareが呼ばれました" << std::endl;
	return x * x;
}

float mySquare(float x) {
	std::cout << "float型のmySquareが呼ばれました" << std::endl;
	return x * x;
}

double mySquare(double x) {
	std::cout << "double型のmySquareが呼ばれました" << std::endl;
	return x * x;
}


int main() {
	int x = 1;
	float y = 0.5;
	double z = 2.1;
	std::cout << mySquare(x) << std::endl;
	std::cout << mySquare(y) << std::endl;
	std::cout << mySquare(z) << std::endl;
}
```

## vol_4課題2(コンソール)

```cpp
#include <iostream>

class Vector3 {
public:
	int x, y;

	Vector3(int _x, int _y, int _z) :
		x(_x),
		y(_y),
		z(_z)
	{
		std::cout << "引数ありのコンストラクタが呼ばれました" << std::endl;
	}

	Vector3() :
		x(0),
		y(0),
		z(0)
	{
		std::cout << "引数なしのコンストラクタが呼ばれました" << std::endl;
	}

	~Vector3() {
		std::cout << "デストラクタが呼ばれました" << std::endl;
	}
};

int main() {
	std::cout << "メイン関数に入りました" << std::endl;
	Vector3 pos1;
	Vector3 pos2(2, 3, 4);
	std::cout << "メイン関数を抜けました" << std::endl;
}
```


## vol_5課題(コンソール)

```cpp
#include <iostream>

void twiceRef(int &x) {
	x *= 2;
}


int main() {

	int num = 3;

	std::cout << num << std::endl;

	twiceRef(num);

	std::cout << num << std::endl;

	return 0;
}
```




## vol_6課題(コンソール)

```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
	int a;
	int b;

	MyClass(int _a, int _b) :
		a(_a),
		b(_b)
	{
	}
};

int main() {
	std::vector<MyClass> vec;

	for (int i = 0; i < 10; i++) {
		vec.emplace_back(MyClass(rand() % 10, rand() % 10));
	}

	for (auto iter = vec.begin(); iter < vec.end(); iter++) {
		std::cout << "(" << iter->a << ", " << iter->b << "), ";
	}

	std::cout << std::endl;

	auto iter = vec.begin();
	while (iter < vec.end()) {
		if (iter->a < iter->b) {
			iter = vec.erase(iter);
		}
		else iter++;
	}

	for (auto iter = vec.begin(); iter < vec.end(); iter++) {
		std::cout << "(" << iter->a << ", " << iter->b << "), ";
	}

	std::cout << std::endl;
}
```



## vol_7課題1(コンソール)

```cpp
#include <iostream>

int main() {

	auto twice = [](int x) {
		return x * 2;
	};

	int num = 3;
	
	std::cout << twice(num) << std::endl;

	return 0;
}
```

## vol_7課題2(コンソール)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::vector<int> vec;
	
	// vectorに0から9の数を入れる
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(i);
	}

	//表示
	for (auto i = vec.begin(); i < vec.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	// 2の倍数を後ろに詰め、削除
	auto rmvIter = std::remove_if(vec.begin(), vec.end(), 
		[](int i) {return i % 2 == 0; }
	);
	vec.erase(rmvIter, vec.end());

	//表示
	for (auto i = vec.begin(); i < vec.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	return 0;
}
```

## vol_7課題3(コンソール)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class MyClass {
public:
	int a;

	MyClass(int _a) :
		a(_a)
	{
	}
};


int main() {

	std::vector<MyClass> vec;

	for (int i = 0; i < 10; i++) {
		vec.emplace_back(MyClass(rand() % 10));
	}

	// vectorの中身を表示
	for (auto i = vec.begin(); i < vec.end(); i++) {
		std::cout << i->a << " ";
	}
	std::cout << std::endl;

	// vecの中から5以下のaを持つ要素を後ろに詰める
	auto rmvIter = std::remove_if(vec.begin(), vec.end(), [](const MyClass& ins) {
		return ins.a <= 5;
	});

	// 実際に削除
	vec.erase(rmvIter, vec.end());

	// vectorの中身を表示
	for (auto i = vec.begin(); i < vec.end(); i++) {
		std::cout << i->a << " ";
	}
	std::cout << std::endl;

	return 0;
}
```



## vol_10課題(コンソール)
```cpp
#include <iostream>
#include <vector>

class MyClass {
public:
	int a;

	MyClass(int _a) :
		a(_a)
	{
	}
};

int main() {
	std::vector<MyClass*> vec;

	// 適当な数でMyClassを追加
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(new MyClass(rand() % 10));
	}

	// vectorの中身を表示
	for (const auto& i : vec) {
		std::cout << i->a << " ";
	}
	std::cout << std::endl;

	// 5以下の要素を削除
	auto it = vec.begin();
	while (it != vec.end()) {
		if ((*it)->a <= 5) {
			delete *it;
			it = vec.erase(it);
		}
		else {
			it++;
		}
	}

	// vectorの中身を表示
	for (const auto& i : vec) {
		std::cout << i->a << " ";
	}
	std::cout << std::endl;

	return 0;
}
```

## vol_11課題(コンソール)

```cpp
#include <iostream>
#include <vector>

class IAnimal {
public:
	double weight;//重さ

	IAnimal(int w) : weight(w) {

	}
	virtual ~IAnimal() = default;

	virtual void talk() {
		std::cout << "基底クラスのtalk関数が呼ばれました。 重さは:" << weight << std::endl;
	}

};

class Dog : public IAnimal {
public:
	Dog(int w) : IAnimal(w) {

	}

	~Dog() = default;

	void talk() override {
		std::cout << "わんわん　重さは:" << weight << std::endl;
	}
};

class Yojo : public IAnimal {
public:
	Yojo(int w) : IAnimal(w) {

	}

	~Yojo() = default;

	void talk() override {
		std::cout << "ふぇぇ…　重さは:" << weight << std::endl;
	}
};

class Cat : public IAnimal {
public:
	Cat(int w) : IAnimal(w) {

	}

	~Cat() = default;

	void talk() override {
		std::cout << "にゃー　重さは:" << weight << std::endl;
	}
};

int main() {
	std::vector<IAnimal*> animals;
	animals.emplace_back(new Dog(10));
	animals.emplace_back(new Yojo(20));
	animals.emplace_back(new Cat(30));
	
	for (const auto& animal : animals) {
		animal->talk();
	}

	return 0;
}
```


## Vol_12課題(コンソール)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Vector2 {
public:
	int x, y;
	Vector2(int _x, int _y)
		:x(_x),
		y(_y)
	{
	}
	~Vector2() {
		std::cout << "Vector2のデストラクタが呼ばれました(x, y) = " 
			<< "(" << x << "," << y << ") " << std::endl;
	}
};

int main() {
	std::vector<std::shared_ptr<Vector2>> vec;

	// 適当な数でMyClassを追加
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(std::make_shared<Vector2>(rand() % 10, rand() % 10));
	}

	// vectorの中身を表示
	for (const auto& i : vec) {
		std::cout << "(" << i->x << "," << i->y << ") ";
	}
	std::cout << std::endl;

	
	// x > yの要素を削除
	auto rmvIter = std::remove_if(vec.begin(), vec.end(), [](const std::shared_ptr<Vector2>& a) {
		return a->x > a->y;
	});
	vec.erase(rmvIter, vec.end());

	// vectorの中身を表示
	for (const auto& i : vec) {
		std::cout << "(" << i->x << "," << i->y << ") ";
	}
	std::cout << std::endl;

	return 0;
}
```