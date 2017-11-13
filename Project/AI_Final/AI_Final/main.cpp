#include "GameManager.h"

int main()
{
	bool contiueLoop = true;

	gpGameManager = new GameApp();
	gpGameManager->init(1000, 1000);

	while (contiueLoop)
	{
		contiueLoop = gpGameManager->updateLoop();
	}

	return 0;
}