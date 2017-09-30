#include "DxLib.h"
#include "GameManager.h"

void Main()
{
	const Font font(18);

	while (System::Update())
	{
		// Z, X, CƒL[‚ğ‰Ÿ‚·‚ÆA©‹@‚ğ’Ç‚¤“GA‚»‚Ìê‚Å‰ñ“]‚·‚é“GA‚Ü‚Á‚·‚®i‚Ş“G‚ğ¶¬
		if (keyState[KEY_INPUT_Z] == 1) {
			gameManager.enemyManager.add(RandomVec2(Window::Width(), Window::Height() / 2.0), Enemy::Stalker);
		}
		if (Input::KeyX.clicked) {
			gameManager.enemyManager.add(RandomVec2(Window::Width(), Window::Height() / 2.0), Enemy::Rotation);
		}
		if (Input::KeyC.clicked) {
			gameManager.enemyManager.add(RandomVec2(Window::Width(), Window::Height() / 2.0), Enemy::Straight);
		}

		gameManager.update();
		gameManager.draw();

		font( L"“G‚Ì”:", gameManager.enemyManager.getEnemyNum()).draw();
	}
}
