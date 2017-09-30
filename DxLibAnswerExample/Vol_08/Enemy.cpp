#include "DxLib.h"
#include "MyGlobal.h"
#include "Enemy.h"
#include "GameManager.h"

const double Enemy::Radius = 24.0;

Enemy::Enemy(double _x, double _y, Kind _kind) :
	x(_x), y(_y),
	vx(0.0), vy(0.0),
	kind(_kind),
	elapsedFrame(0)
{
}

void Enemy::update() {
	if (kind == Stalker) {
		Player& player = gameManager.player;
		const double Speed = 1.5;
		normalize(x, y, player.x, player.y, &vx, &vy);
		vx *= Speed;
		vy *= Speed;
		x += vx;
		y += vy;
	}
	else if (kind == Rotation) {
		double angle = elapsedFrame * 0.02;
		vx = 1.0 * cos(angle);
		vy = 1.0 * sin(angle);
	}
	else if (kind == Straight) {
		vx = 0.0;
		vy = 1.0;
	}
	x += vx;
	y += vy;
	elapsedFrame++;
}

void Enemy::draw() {
	if (kind == Stalker) {
		DrawCircle(x, y, static_cast<int>(Radius), GetColor(255, 0, 0));
	}
	else if (kind == Rotation) {
		DrawCircle(x, y, static_cast<int>(Radius), GetColor(255, 128, 0));
	}
	else if (kind == Straight) {
		DrawCircle(x, y, static_cast<int>(Radius), GetColor(255, 0, 128));
	}
}
