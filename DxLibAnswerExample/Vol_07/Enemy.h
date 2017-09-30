#pragma once
#include <Siv3D.hpp>

class Enemy {
public:
	Vec2 pos;
	Vec2 velocity;
	Enemy(const Vec2& _pos);
	void update();
	void draw();
};