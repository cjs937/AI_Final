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

const int GRID_SQUARE_SIZE = 32;
const IDType BACKGROUND_ID = STARTING_SEQUENTIAL_ID;
const IDType SPAWN_LOCATION_ID = STARTING_SEQUENTIAL_ID + 1 ;
const IDType WALL_ID = STARTING_SEQUENTIAL_ID + 2;
const string SPRITE_PATH = "../sprites/";

Editor::Editor() : Game()
{
	mpGrid = NULL;
	mpGridVisualizer = NULL;
	mpLoader = NULL;
	mTypeOfObject = BLOCKING_VALUE; // set the default draw to a "wall"
	mCounter = 0; // initialize this to nothing will use to track current sprite drawn
}

Editor::~Editor()
{
	cleanup();
}

bool Editor::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{
		return false;
	}

	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpLoader = new AssetLoader();

	mpLoader->loadAssets();
	mCounter = mpLoader->getAssetIdMax();

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
	al_get_mouse_state( &mouseState );
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state( &keyState );

	if( al_mouse_button_down( &mouseState, 1 ) && !al_mouse_button_down(&mPreviousMouseState, 1))//left mouse click
	{
		mpGrid->setValueAtPixelXY( mouseState.x, mouseState.y, getTypeOffObject() );
	}
	else if( al_mouse_button_down( &mouseState, 2 ) )//right mouse down
	{
		mpGrid->setValueAtPixelXY( mouseState.x, mouseState.y, CLEAR_VALUE );
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_Q) && !al_key_down(&mPreviousKeyState, ALLEGRO_KEY_Q)) // pressed p button
	{
		setTypeOfObject(1);
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_E) && !al_key_down(&mPreviousKeyState, ALLEGRO_KEY_E)) // pressed w button
	{
		setTypeOfObject(-1);
	}

	mPreviousKeyState = keyState;
	mPreviousMouseState = mouseState;

	draw();

	//should be last thing in processLoop
	Game::processLoop();
}

void Editor::draw()
{
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite(BACKGROUND_SPRITE_ID);
	pBackgroundSprite->draw(*(mpGraphicsSystem->getBackBuffer()), 0, 0);
	int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
	//get any non-zero squares and make them desired sprites
	for (int i = 0; i < size; i++)
	{
		if (mpGrid->getValueAtIndex(i) != 0)
		{
			drawLevel(mpGrid->getULCornerOfSquare(i), mpSpriteManager->getSprite(mpGrid->getValueAtIndex(i)));
		}
	}
}

void Editor::drawLevel(Vector2D pos, Sprite* spriteToDraw)
{
	spriteToDraw->drawScaled(*(mpGraphicsSystem->getBackBuffer()), pos.getX(), pos.getY(), mpGrid->getGridWidth(), mpGrid->getGridWidth(), 0);
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

void Editor::saveGrid( ofstream& theStream )
{
	mpGrid->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream )
{
	mpGrid->load(theStream);
}
