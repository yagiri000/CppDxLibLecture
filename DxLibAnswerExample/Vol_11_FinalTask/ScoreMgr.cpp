#include <iostream>
#include "GameManager.h"

ScoreManager::ScoreManager() :
	score(0)
{
}

void ScoreManager::addScore(int n) {
	score += n;
}

int ScoreManager::getScore() {
	return score;
}

void ScoreManager::addDamagedNum() {
	damagedNum++;
}

int ScoreManager::getDamagedNum() {
	return damagedNum;
}

void ScoreManager::update() {

}

void ScoreManager::draw() const {
	gameManager.font(L"SCORE:", score).draw(Vec2(10.0, 30.0 * 0.0));
	gameManager.font(L"”í’e”:", damagedNum).draw(Vec2(10.0, 30.0 * 1.0));
}