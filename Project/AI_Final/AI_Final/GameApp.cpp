#include "GameApp.h"
#include "Timer.h"
#include "SaveSystem.h"

GameApp* gpGameApp = NULL;

GameApp::GameApp()//:Saveable(new GameSaveData()) /*Uncomment for save system unit test*/
{}

GameApp::~GameApp()
{}

void GameApp::init(int _screenWidth, int _screenHeight)
{
	mpSaveSystem = new SaveSystem();


	/*Unit test for save system*/
	//mpSaveSystem->addObject(this);

	//mpSaveSystem->saveState(SAVEFILE_NAME);

	//static_cast<GameSaveData*>(mSaveData)->test = 2;

	//mpSaveSystem->loadFromFile(SAVEFILE_NAME);

	//std::cout << static_cast<GameSaveData*>(mSaveData)->test << std::endl;

	mpLoopTimer = new Timer();
	mpLoopTimer->start();
}

void GameApp::startLoop()
{
	mLoopStartTime = mpLoopTimer->getElapsedTime();
}

bool GameApp::updateLoop()
{
	startLoop();

	return endLoop();
}

bool GameApp::endLoop()
{
	mPrevFrameTime = mpLoopTimer->getElapsedTime();

	mpLoopTimer->sleepUntilElapsed(mLoopStartTime + FPS_MS - mPrevFrameTime);

	return mContinueLoop;
}

void GameApp::cleanup()
{
	if (mpSaveSystem != NULL)
	{
		delete mpSaveSystem;

		mpSaveSystem = NULL;
	}

	if (mpLoopTimer != NULL)
	{
		mpLoopTimer = NULL;

		mpSaveSystem = NULL;
	}
}


float GameApp::getDeltaTime()
{
	return mpLoopTimer->getElapsedTime() - mPrevFrameTime;
}