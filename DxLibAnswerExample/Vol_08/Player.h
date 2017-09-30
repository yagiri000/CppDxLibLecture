#pragma once
#include <Siv3D.hpp>

class Player {
public:
	static const double Speed;
	Vec2 pos;
	Player();
	void update();
	void draw();
};