#include "Enemy.h"
#include "MyGlobal.h"
#include <iostream>

const double IEnemy::Radius = 30.0;

const double EnemySinMove::SinOmega = 0.02;
const double EnemySinMove::SpeedX = 2.0;
const double EnemySinMove::SpeedY = 1.0;
const unsigned int EnemySinMove::Color = 0xFF0000;

const double EnemyRotation::Speed = 2.0;
const double EnemyRotation::RotationOmega = 0.04;
const unsigned int EnemyRotation::Color = 0xFF8800;

const double EnemyStraight::Speed = 2.0;
const unsigned int EnemyStraight::Color = 0xFF0088;


IEnemy::IEnemy(double _x, double _y) :
	x(_x), y(_y),
	vx(0.0), vy(0.0)
{
}

EnemySinMove::EnemySinMove(double _x, double _y) :
	IEnemy(_x, _y)
{
}

void EnemySinMove::update() {
	// SinãOìπÇ≈ìÆÇ≠
	vx = sin((double)elapsedFrame * SinOmega) * SpeedX;
	vy = SpeedY;
	x += vx; y += vy;
	elapsedFrame++;
}

void EnemySinMove::draw() const {
	DrawCircle(x, y, Radius, Color);
}

EnemyRotation::EnemyRotation(double _x, double _y) :
	IEnemy(_x, _y)
{
}

void EnemyRotation::update() {
	double angle = (double)elapsedFrame * RotationOmega;
	vx = Speed * cos(angle);
	vy = Speed * sin(angle);
	x += vx; y += vy;
	elapsedFrame++;
}

void EnemyRotation::draw() const {
	DrawCircle(x, y, Radius, Color);
}

EnemyStraight::EnemyStraight(double _x, double _y) :
	IEnemy(_x, _y)
{
	// ÉâÉìÉ_ÉÄÇ»ë¨ìxÇê›íË
	randomInCircle(Speed, &vx, &vy);
}

void EnemyStraight::update() {
	// Ç‹Ç¡Ç∑ÇÆìÆÇ≠
	x += vx; y += vy;
}

void EnemyStraight::draw() const {
	DrawCircle(x, y, Radius, Color);
}
