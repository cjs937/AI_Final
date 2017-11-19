#pragma once
#include "Trackable.h"
#include "allegro5\allegro_font.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;


class Timer;
class SaveSystem;
class GameMessageManager;
class GraphicsSystem;
class GraphicsBufferManager;
class SpriteManager;

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

	void draw();

	void cleanup();

	void quit();

	//Getters
	SaveSystem* getSaveSystem() { return mpSaveSystem; };
	GameMessageManager* getMessageManager() { return mpMessageManager; };
	ALLEGRO_FONT* getDefaultFont() { return mpDefaultFont; }

	float getDeltaTime();
	float getCurrentTime();


private:
	Timer* mpLoopTimer;
	SaveSystem* mpSaveSystem;
	GameMessageManager* mpMessageManager;
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	ALLEGRO_FONT* mpDefaultFont;

	bool mContinueLoop = true;
	float mPrevFrameTime;
	float mLoopStartTime;

	void installAllegro();
};

extern GameApp* gpGameApp;
