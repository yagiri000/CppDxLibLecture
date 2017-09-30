#include "Enemy.h"

const double IEnemy::Radius = 30.0;

const double EnemySinMove::SinOmega = 0.02;
const double EnemySinMove::SpeedX = 2.0;
const double EnemySinMove::SpeedY = 1.0;
const Color EnemySinMove::Color_(255, 0, 0);

const double EnemyRotation::Speed = 2.0;
const double EnemyRotation::RotationOmega = 0.04;
const Color EnemyRotation::Color_(255, 128, 0);

const double EnemyStraight::Speed = 2.0;
const Color EnemyStraight::Color_(255, 0, 128);


IEnemy::IEnemy(double _x, double _y):
	x(_x), y(_y),
	vx(0.0), vy(0.0)
{
}

EnemySinMove::EnemySinMove(const Vec2 & _pos):
IEnemy(_pos)
{
}

void EnemySinMove::update() {
	// SinãOìπÇ≈ìÆÇ≠
	velocity = Vec2(sin((double)eFrame * SinOmega) * SpeedX, SpeedY);
	x += vx; y+= vy;
	eFrame++;
}

void EnemySinMove::draw() const {
	Circle(pos, Radius).draw(Color_);
}

EnemyRotation::EnemyRotation(const Vec2 & _pos) :
	IEnemy(_pos) 
{
}

void EnemyRotation::update() {
	// ë¨ìxÇâÒì]Ç≥ÇπÇÈ
	velocity = Vec2(Speed, 0.0).rotated((double)eFrame * RotationOmega);
	x += vx; y+= vy;
	eFrame++;
}

void EnemyRotation::draw() const {
	Circle(pos, Radius).draw(Color_);
}

EnemyStraight::EnemyStraight(const Vec2 & _pos) :
	IEnemy(_pos) 
{
	// ÉâÉìÉ_ÉÄÇ»ë¨ìxÇê›íË
	velocity = RandomVec2(Speed);
}

void EnemyStraight::update() {
	// Ç‹Ç¡Ç∑ÇÆìÆÇ≠
	x += vx; y+= vy;
}

void EnemyStraight::draw() const {
	Circle(pos, Radius).draw(Color_);
}
