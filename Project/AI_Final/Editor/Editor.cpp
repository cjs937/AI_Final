#include <fstream>
#include <allegro5/allegro_primitives.h>

#include "Game.h"
#include "Editor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "assetLoader.h"

using namespace std;


Editor::Editor() : Game()
{
	mpGrid = NULL;
	mpGridVisualizer = NULL;
	mpLoader = NULL;
	mTypeOfObject = BLOCKING_VALUE; // set the default draw to a "wall"
	mCounter = 0; // initialize this to nothing will use to track current sprite drawn
	mLevelCounter = 0;
	mCurrentLevel = 0;
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init(int _width, int _height)
{
	bool retVal = Game::init(_width, _height);
	if (retVal == false)
	{
		return false;
	}

	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpLoader = new AssetLoader();

	mpLoader->loadAssets();
	mCounter = mpLoader->getAssetIdMax();
	mLevelCounter = mpLoader->getLevelIdMax();

	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGrid;
	mpGrid = NULL;
	delete mpLoader;
	mpLoader = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		mpGrid->setValueAtPixelXY(mouseState.x, mouseState.y, getTypeOffObject());
	}
	else if (al_mouse_button_down(&mouseState, 2))//right mouse down
	{
		mpGrid->setValueAtPixelXY(mouseState.x, mouseState.y, CLEAR_VALUE);
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_Q) && !al_key_down(&mPreviousKeyState, ALLEGRO_KEY_Q)) // pressed q button
	{
		setTypeOfObject(1);
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_E) && !al_key_down(&mPreviousKeyState, ALLEGRO_KEY_E)) // pressed e button
	{
		setTypeOfObject(-1);
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && !al_key_down(&mPreviousKeyState, ALLEGRO_KEY_RIGHT)) // pressed => button
	{
		setCurrentLevel(1);
		loadLevel();
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && !al_key_down(&mPreviousKeyState, ALLEGRO_KEY_LEFT)) // pressed <= button
	{
		setCurrentLevel(-1);
		loadLevel();
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_S)) // pressed S button
	{
		saveLevel();
	}

	mPreviousKeyState = keyState;
	mPreviousMouseState = mouseState;

	draw();

	//should be last thing in processLoop
	Game::processLoop();
}

void Editor::draw()
{
	mpGrid->draw(mpGraphicsSystem->getBackBuffer());
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::setTypeOfObject(int var)
{
	mTypeOfObject += var;
	if (mTypeOfObject >= mCounter)
		mTypeOfObject = 1;
	if (mTypeOfObject == 0)
		mTypeOfObject = mCounter - 1;
}

void Editor::setCurrentLevel(int var)
{
	mCurrentLevel += var;
	if (mCurrentLevel >= mLevelCounter)
		mCurrentLevel = 0;
	if (mCurrentLevel < 0)
		mCurrentLevel = mLevelCounter - 1;
}

void Editor::saveGrid(ofstream& theStream)
{
	mpGrid->save(theStream);
}

void Editor::load(std::ifstream& theStream)
{
	mpGrid->loadGrid(theStream);
}

void Editor::loadLevel()
{
	//std::string* levelInput;  
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	if (pEditor != NULL)
	{
		//levelInput = 
		ifstream theStream(mpLoader->getLevelName(mCurrentLevel));
		pEditor->load(theStream);
		theStream.close();
		//pEditor->getGridVisualizer()->setModified();
		cout << "Grid loaded!\n";
		Sleep(1000);//very bogus
	}
}

void Editor::saveLevel()
{
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	if (pEditor != NULL)
	{
		ofstream theStream(mpLoader->getLevelName(mCurrentLevel));
		pEditor->saveGrid(theStream);
		theStream.close();
		cout << "Grid saved!\n";
		Sleep(1000);//very bogus
	}
}