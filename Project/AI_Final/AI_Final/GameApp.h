#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "Game.h"
#include "Defines.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;

//default sprite IDs
//const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType WALL_SPRITE_ID = 3;
const IDType CIRCLE_SPRITE_ID = 4;

const IDDescriptor PLAYER_ID = "player";
const IDDescriptor AI_ID = "enemy";

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
class Grid;
class GridGraph;
class GridPathfinder;
enum PathfinderType;

class AIUnit;

class GameApp : public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init(int _screenWidth, int _screenHeight) override;

	//do stuff before beginning loop
	virtual void beginLoop() override;

	//process the loop
	virtual void processLoop() override;

	//do stuff at end of loop and return whether it should exit or not
	virtual bool endLoop() override;

	virtual void draw() override;

	virtual void cleanup() override;

	void quit();

	//Getters
	SaveSystem* getSaveSystem() { return mpSaveSystem; };
	GameMessageManager* getMessageManager() { return mpMessageManager; };
	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; };
	GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };
	SpriteManager* getSpriteManager() { return mpSpriteManager; };
	UnitManager* getUnitManager() { return mpUnitManager; };
	AssetLoader* getAssetLoader() { return mpLoader; };
	DebugSystem* getDebugSystem() { return mpDebugSystem; };
	Grid* getGrid() { return mpGrid; };
	GridGraph* getGridGraph() { return mpGridGraph; };
	GridPathfinder* getPathfinder() { return mpPathfinder; };

	float getDeltaTime();
	float getCurrentTime(); 

	void setPathfinder(PathfinderType _type);

	//loadLevel
	void loadGrid(std::ifstream& theStream);
	void loadLevel();

private:
	AssetLoader* mpLoader;
	SaveSystem* mpSaveSystem;
	GameMessageManager* mpMessageManager;
	UnitManager* mpUnitManager;
	InputSystem* mpInputSystem;
	DebugSystem* mpDebugSystem;

	Grid* mpGrid;
	GridGraph* mpGridGraph;
	GridPathfinder* mpPathfinder;

	bool mContinueLoop = true;
	float mPrevFrameTime;
	float mLoopStartTime;

	void updateSystems();
};

extern GameApp* gpGameApp;
#endif
