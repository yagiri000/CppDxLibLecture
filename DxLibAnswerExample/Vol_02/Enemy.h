#pragma once
#include <Siv3D.hpp>

class Enemy {
public:
	Vec2 pos;

	Enemy(Vec2 _pos);
	void update();
	void draw();
};