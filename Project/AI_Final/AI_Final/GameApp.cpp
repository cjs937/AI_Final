#include "GameApp.h"
#include <cmath>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "Timer.h"
#include "SaveSystem.h"
#include "GameMessageManager.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "UnitManager.h"
#include "InputSystem.h"
#include "AssetLoader.h"
#include "DebugSystem.h"
#include "AIUnit.h"
#include "Grid.h"
#include "GridGraph.h"
#include "AStarPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "Path.h"

GameApp* gpGameApp = NULL;

GameApp::GameApp()
{
	gpGame = this;
}

GameApp::~GameApp()
{}

bool GameApp::init(int _screenWidth, int _screenHeight)
{
	Game::init(_screenWidth, _screenHeight);

	mpSaveSystem = new SaveSystem();

	mpMessageManager = new GameMessageManager();
	
	mpGraphicsBufferManager->init();

	mpInputSystem = new InputSystem();

	mpDebugSystem = new DebugSystem();

	mpGrid = new Grid(_screenWidth, _screenHeight, GRID_SQUARE_SIZE);

	mpLoader = new AssetLoader();

	SharedUnitData* unitData = new SharedUnitData(500.0f, 10000.0f, 100.0f, 10.0f, 1.0f, 5.0f, .8f, 5000.0f, 10000.0f, 15, 3);

	mpUnitManager = new UnitManager(unitData);

	mpLoader->loadAssets();
	loadLevel();

	mpGridGraph = new GridGraph(mpGrid);
	mpGridGraph->init();

	setPathfinder(ASTAR);

	//Unit manager should be initialized after grid & asset loader because it needs their data
	mpUnitManager->init();


	//mpLoader->loadAssets();

	//hide the mouse
	if (!al_hide_mouse_cursor(mpGraphicsSystem->getDisplay()))
	{
		printf("Mouse cursor not able to be hidden!\n");
	}

	mpLoopTimer->start();

	//Unit test - adds an AI and player unit near each other
	//mpUnitManager->addUnit(PLAYER, Vector2D(100, 100), 1, Vector2D(), 0);
	//mpUnitManager->addUnit(AI, Vector2D(150, 100), 1, Vector2D(), 0);

	return true;
}

void GameApp::beginLoop()
{
	//mpLoopTimer->start();
	mLoopStartTime = mpLoopTimer->getElapsedTime();
}

void GameApp::processLoop()
{
	updateSystems();

	draw();
}

void GameApp::updateSystems()
{
	float dt = getDeltaTime();

	mpMessageManager->processMessagesForThisframe();

	mpInputSystem->update();

	mpUnitManager->update(dt);

	mpDebugSystem->update();
}

void GameApp::draw()
{
	GraphicsBuffer* backBuffer = mpGraphicsSystem->getBackBuffer();

	backBuffer->clear();

	Game::draw();

	//[draw things here]
	mpGrid->draw(backBuffer);
	mpUnitManager->draw(backBuffer);

	mpDebugSystem->draw(backBuffer);

	mpGraphicsSystem->swap();
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

	if (mpMessageManager != NULL)
	{
		delete mpMessageManager;

		mpMessageManager = NULL;
	}

	if (mpUnitManager != NULL)
	{
		delete mpUnitManager;

		mpUnitManager = NULL;
	}

	if (mpInputSystem != NULL)
	{
		delete mpMessageManager;

		mpInputSystem = NULL;
	}

	if (mpDebugSystem != NULL)
	{
		delete mpDebugSystem;

		mpInputSystem = NULL;
	}

	if (mpLoader != NULL)
	{
		delete mpLoader;

		mpLoader = NULL;
	}

	if (mpGrid != NULL)
	{
		delete mpGrid;

		mpGrid = NULL;
	}

	if (mpGridGraph != NULL)
	{
		delete mpGridGraph;

		mpGridGraph = NULL;
	}

	if (mpPathfinder != NULL)
	{
		delete mpPathfinder;
		mpPathfinder = NULL;
	}

	Game::cleanup();
}


float GameApp::getDeltaTime()
{
	return abs(mpLoopTimer->getElapsedTime() - mPrevFrameTime);
}


float GameApp::getCurrentTime()
{
	return mpLoopTimer->getElapsedTime();
}


void GameApp::quit()
{
	mContinueLoop = false;
}

void GameApp::load(std::ifstream& theStream)
{
	mpGrid->loadGrid(theStream);
	//mpGrid->load(theStream);
}

void GameApp::loadLevel()
{
	//std::string* levelInput;  
	GameApp* pGameApp = dynamic_cast<GameApp*>(gpGame);
	if (pGameApp != NULL)
	{
		//levelInput = 
		ifstream theStream(mpLoader->getLevelName(0));
		pGameApp->load(theStream);
		theStream.close();
		//pEditor->getGridVisualizer()->setModified();
		cout << "Grid loaded!\n";
		Sleep(1000);//very bogus
	}
}

void GameApp::setPathfinder(PathfinderType _type)
{
	if (mpPathfinder != NULL)
	{
		if (mpPathfinder->getType() == _type)
			return;

		delete mpPathfinder;
	}
	switch (_type)
	{
	case(ASTAR):
	{
		mpPathfinder = new AStarPathfinder(mpGridGraph);
		break;
	}
	default:
		mpPathfinder = NULL;
	}
}