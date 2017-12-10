#include "GameApp.h"
#include <iostream>
#include "MemoryTracker.h"

int main()
{
	MemoryTracker memoryTracker;

	bool contiueLoop = true;

	gpGameApp = new GameApp();
	gpGameApp->init(WIDTH, HEIGHT);

	while (contiueLoop)
	{
		gpGameApp->beginLoop();
		gpGameApp->processLoop();
		contiueLoop = gpGameApp->endLoop();
	}

	delete gpGameApp;

	gpGameApp = NULL;

	gMemoryTracker.reportAllocations(std::cout);

	system("pause");

	return 0;
}