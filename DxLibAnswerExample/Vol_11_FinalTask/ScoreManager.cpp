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
	DrawFormatStringToHandle(10, 30 * 3, GetColor(255, 255, 255), gameManager.fontHandle, "SCORE:%d", score);
	DrawFormatStringToHandle(10, 30 * 4, GetColor(255, 255, 255), gameManager.fontHandle, "”í’e”:%d", damagedNum);
}