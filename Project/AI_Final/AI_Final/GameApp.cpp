#include "GameManager.h"
#include "Timer.h"

GameApp* gpGameApp = NULL;

GameApp::GameApp()
{}

GameApp::~GameApp()
{}

void GameApp::init(int _screenWidth, int _screenHeight)
{
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

float GameApp::getDeltaTime()
{
	return mpLoopTimer->getElapsedTime() - mPrevFrameTime;
}