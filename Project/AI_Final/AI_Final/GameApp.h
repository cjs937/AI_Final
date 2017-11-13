#pragma once
#include "Trackable.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;

class Timer;

class GameApp : public Trackable
{
public:
	GameApp();
	~GameApp();

	void init(int screenWidth, int screenHeight);

	//do stuff before beginning loop
	void startLoop();

	//process the loop
	bool updateLoop();

	//do stuff at end of loop and return whether it should exit or not
	bool endLoop();

	float getDeltaTime();

	//Getters




private:
	Timer* mpLoopTimer;
	bool mContinueLoop = true;
	float mPrevFrameTime;
	float mLoopStartTime;
};

extern GameApp* gpGameManager;
