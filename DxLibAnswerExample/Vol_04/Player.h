#pragma once
#include <Siv3D.hpp>

class Player {
public:
	Vec2 pos;
	double speed;
	Player();
	void update();
	void draw();
};