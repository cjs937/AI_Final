#pragma once

#include "Game.h"
#include <fstream>

#include "Vector2D.h"

/*Editor - class to hold all application related info.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class GraphicsBuffer;
class Sprite;
class Grid;
class GridVisualizer;
class GraphicsBuffer;
class AssetLoader;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Editor : public Game
{
public:
	Editor();
	virtual ~Editor();

	inline Grid* getGrid() { return mpGrid; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };

	virtual bool init(int _width, int _height);
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void saveGrid( std::ofstream& theStream );
	void load( std::ifstream& theStream );

	//these are fore setting and getting the type of object
	void setTypeOfObject(int var);
	inline int getTypeOffObject() const { return mTypeOfObject; };

	//sets the current level
	void setCurrentLevel(int var);
	inline int getCurrentLevel() const { return mCurrentLevel; };

    //draw level
	void draw();

	//loadLevel
	void loadLevel();
	void saveLevel();

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;

	AssetLoader* mpLoader;

	int mTypeOfObject, mCounter, mCurrentLevel, mLevelCounter;
	IDType mpWallIconBufferID;
	IDType mpSpawnIconBufferID;
	ALLEGRO_KEYBOARD_STATE mPreviousKeyState;
	ALLEGRO_MOUSE_STATE mPreviousMouseState;

};