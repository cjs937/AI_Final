#pragma once
#include "Trackable.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;


class Timer;
class SaveSystem;
class GameMessageManager;

class GameApp : public Trackable
{
public:
	GameApp();
	~GameApp();

	void init(int _screenWidth, int _screenHeight);

	//do stuff before beginning loop
	void startLoop();

	//process the loop
	bool updateLoop();

	//do stuff at end of loop and return whether it should exit or not
	bool endLoop();

	void cleanup();

	void quit();

	//Getters
	SaveSystem* getSaveSystem() { return mpSaveSystem; };
	GameMessageManager* getMessageManager() { return mpMessageManager; };
	float getDeltaTime();
	float getCurrentTime();


private:
	Timer* mpLoopTimer;
	SaveSystem* mpSaveSystem;
	GameMessageManager* mpMessageManager;

	bool mContinueLoop = true;
	float mPrevFrameTime;
	float mLoopStartTime;

	void installAllegro();
};

extern GameApp* gpGameApp;
