#pragma once
#include "DxLib.h"
#include "Player.h"

class Enemy {
public:
	double x, y;
	double vx, vy;
	Player *playerPtr;
	Enemy(double _x, double _y);
	void update();
	void draw();

	// �v���C���[�ւ̃|�C���^���擾����֐�
	void setPlayerPtr(Player *ptr_);
};