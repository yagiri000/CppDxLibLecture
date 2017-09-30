#pragma once
#include <Siv3D.hpp>

class IEnemy {
public:
	static const double Radius;
	Vec2 pos;
	Vec2 velocity;
	IEnemy(const Vec2& _pos);
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual ~IEnemy() = default;
};

// Sin‹O“¹‚ğ•`‚¢‚Ä“®‚­“G
class EnemySinMove : public IEnemy {
public:
	static const double SinOmega;
	static const double SpeedX;
	static const double SpeedY;
	static const Color Color_;
	
	int eFrame;

	EnemySinMove(const Vec2& _pos);
	void update() override;
	void draw() const override;
	~EnemySinMove() = default;
};

// ‰~‰^“®‚ğ‚·‚é“G
class EnemyRotation : public IEnemy {
public:
	static const double Speed;
	static const double RotationOmega;
	static const Color Color_;

	int eFrame;

	EnemyRotation(const Vec2& _pos);
	void update() override;
	void draw() const override;
	~EnemyRotation() = default;
};

// ƒ‰ƒ“ƒ_ƒ€‚È•ûŒü‚ÉA’¼ü‚ÉˆÚ“®‚·‚é“G
class EnemyStraight : public IEnemy {
public:
	static const double Speed;
	static const Color Color_;

	EnemyStraight(const Vec2& _pos);
	void update() override;
	void draw() const override;
	~EnemyStraight() = default;
};
