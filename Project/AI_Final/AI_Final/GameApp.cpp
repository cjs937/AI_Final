#include "GameApp.h"
#include "Timer.h"
#include "SaveSystem.h"
#include "GameMessageManager.h"
#include "allegro5\allegro.h"

GameApp* gpGameApp = NULL;

GameApp::GameApp()
{}

GameApp::~GameApp()
{
}

void GameApp::init(int _screenWidth, int _screenHeight)
{
	installAllegro();

	mpSaveSystem = new SaveSystem();

	mpMessageManager = new GameMessageManager();

	mpLoopTimer = new Timer();
	mpLoopTimer->start();
}

void GameApp::installAllegro()
{
	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
	}
}

void GameApp::startLoop()
{
	mLoopStartTime = mpLoopTimer->getElapsedTime();
}

bool GameApp::updateLoop()
{
	startLoop();

	//[process loop here]

	return endLoop();
}

bool GameApp::endLoop()
{
	mPrevFrameTime = mpLoopTimer->getElapsedTime();

	mpLoopTimer->sleepUntilElapsed(mLoopStartTime + FPS_MS - mPrevFrameTime);

	if(!mContinueLoop)
		cleanup();

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
		delete mpLoopTimer;

		mpLoopTimer = NULL;
	}

	if (mpMessageManager != NULL)
	{
		delete mpMessageManager;

		mpMessageManager = NULL;
	}
}


float GameApp::getDeltaTime()
{
	return mpLoopTimer->getElapsedTime() - mPrevFrameTime;
}


float GameApp::getCurrentTime()
{
	return mpLoopTimer->getElapsedTime();
}


void GameApp::quit()
{
	mContinueLoop = false;
}