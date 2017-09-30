# include "Enemy.h"

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


IEnemy::IEnemy(const Vec2& _pos):
	pos(_pos),
	velocity(0.0, 0.0)
{
}

EnemySinMove::EnemySinMove(const Vec2 & _pos):
IEnemy(_pos)
{
}

void EnemySinMove::update() {
	// SinãOìπÇ≈ìÆÇ≠
	velocity = Vec2(sin((double)eFrame * SinOmega) * SpeedX, SpeedY);
	pos += velocity;
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
	pos += velocity;
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
	pos += velocity;
}

void EnemyStraight::draw() const {
	Circle(pos, Radius).draw(Color_);
}
