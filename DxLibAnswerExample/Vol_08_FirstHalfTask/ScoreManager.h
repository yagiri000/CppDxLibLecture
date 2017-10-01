#pragma once
#include "DxLib.h"

class ScoreManager{
private:
	int score;
	int damagedNum;
public:
	ScoreManager();
	void addScore(int n);
	int getScore();
	void addDamagedNum();
	int getDamagedNum();
	void update();
	void draw() const;
};