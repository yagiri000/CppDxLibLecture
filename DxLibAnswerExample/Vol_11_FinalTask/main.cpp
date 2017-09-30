#include "GameManager.h"

void Main() {
	// フォントをロード
	gameManager.load();

	while (System::Update()) {
		gameManager.update();
		gameManager.draw();
	}
}
