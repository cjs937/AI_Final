#pragma once
#include "Trackable.h"
#include "allegro5\allegro_font.h"
#include "Defines.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;

//default sprite IDs
//const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType WALL_SPRITE_ID = 3;
const IDType CIRCLE_SPRITE_ID = 4;

class Timer;
class SaveSystem;
class GameMessageManager;
class GraphicsSystem;
class GraphicsBufferManager;
class SpriteManager;
class UnitManager;
class InputSystem;
class AssetLoader;
class DebugSystem;

class AIUnit;

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
	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; };
	GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };
	SpriteManager* getSpriteManager() { return mpSpriteManager; };
	UnitManager* getUnitManager() { return mpUnitManager; };

	ALLEGRO_FONT* getDefaultFont() { return mpDefaultFont; }
	float getDeltaTime();
	float getCurrentTime(); 

private:
	AssetLoader* mpLoader;
	Timer* mpLoopTimer;
	SaveSystem* mpSaveSystem;
	GameMessageManager* mpMessageManager;
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	UnitManager* mpUnitManager;
	InputSystem* mpInputSystem;
	DebugSystem* mpDebugSystem;

	ALLEGRO_FONT* mpDefaultFont;

	bool mContinueLoop = true;
	float mPrevFrameTime;
	float mLoopStartTime;

	void installAllegro();
	void updateSystems();
};

extern GameApp* gpGameApp;
