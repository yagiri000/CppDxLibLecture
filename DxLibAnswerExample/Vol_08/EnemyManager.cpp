#include "EnemyManager.h"
#include <algorithm>

void EnemyManager::update() {
	for (auto&& enemy : enemies) {
		enemy.update();
	}
	checkDelete();
}

void EnemyManager::draw() {
	for (auto&& enemy : enemies) {
		enemy.draw();
	}
}

void EnemyManager::add(const Enemy& enemy) {
	enemies.emplace_back(enemy);
}

size_t EnemyManager::getEnemyNum(){
	return enemies.size();
}

void EnemyManager::checkDelete() {
	auto it = enemies.begin();

	// ‰æ–ÊŠO‚Ì“G‚ğíœ
	auto rmvIter = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) {

		// “G‚Ì‰~ó‚Ì“–‚½‚è”»’è‚Æ‰æ–ÊƒTƒCƒY‚ÌlŠp‚Ì“–‚½‚è”»’è‚ğæ‚èA“–‚½‚Á‚Ä‚¢‚È‚©‚Á‚½‚ç‰æ–ÊŠO‚É‚¢‚é‚Æ”»’è
		return !Circle(enemy.pos, enemy.Radius).intersects(Rect(Window::Size()));
	});

	enemies.erase(rmvIter, enemies.end());
}