#include "GameApp.h"
#include <iostream>
#include "MemoryTracker.h"

int main()
{
	MemoryTracker memoryTracker;

	bool contiueLoop = true;

	gpGameApp = new GameApp();
	gpGameApp->init(1000, 1000);

	while (contiueLoop)
	{
		contiueLoop = gpGameApp->updateLoop();
	}

	delete gpGameApp;

	gpGameApp = NULL;

	gMemoryTracker.reportAllocations(std::cout);

	system("pause");

	return 0;
}