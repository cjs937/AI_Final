#ifndef GAME_H
#pragma once
#define GAME_H


/* Game - base class for actual application class

	Dean Lawson
	Champlain College
	2011
*/
#include <Trackable.h>
#include <Timer.h>
#include "Defines.h"

class MemoryTracker;
class PerformanceTracker;
class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class Game;
class LevelEditor;
class Hud;
struct ALLEGRO_FONT;

extern PerformanceTracker* gpPerformanceTracker;
extern Game* gpGame;

const IDType BACKGROUND_SPRITE_ID = 0;
//const IDType SPAWN_SPRITE_ID = 1;
//const IDType WALL_SPRITE_ID = 2;

class Game:public Trackable
{
public:
	Game();
	virtual ~Game();

	virtual bool init(int _width, int _height);
	bool initAllegro();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	virtual void draw();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	inline void markForExit() { mShouldExit = true; };
	inline Hud* getHud() { return mpHud; };

protected:
	Hud* mpHud;
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	float mLoopTargetTime;
	bool mShouldExit;
	//should be somewhere else
	ALLEGRO_FONT* mpFont;

};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge
float mapRotationToRange( float rotation, float low, float high );
float lerp(int value, int start, int end);//returns float representing how far value is between start and end

const double PI = std::atan(1.0)*4;//could proved useful!
#endif // !GAME_H
