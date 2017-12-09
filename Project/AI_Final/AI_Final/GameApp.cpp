#include "GameApp.h"

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

GameApp* gpGameApp = NULL;

GameApp::GameApp()
{}

GameApp::~GameApp()
{
}

void GameApp::init(int _screenWidth, int _screenHeight)
{
	installAllegro();

	mpGraphicsSystem = new GraphicsSystem();

	mpSaveSystem = new SaveSystem();

	mpMessageManager = new GameMessageManager();

	mpGraphicsBufferManager = new GraphicsBufferManager();

	mpSpriteManager = new SpriteManager();

	mpUnitManager = new UnitManager();

	mpInputSystem = new InputSystem();

	mpLoopTimer = new Timer();

	mpGraphicsSystem->init(_screenWidth, _screenHeight);

	mpGraphicsBufferManager->init();

	//hide the mouse
	if (!al_hide_mouse_cursor(mpGraphicsSystem->getDisplay()))
	{
		printf("Mouse cursor not able to be hidden!\n");
	}

	mpLoopTimer->start();

	mpUnitManager->addUnit(AI, Vector2D(200, 200), 1, Vector2D(), 0);
}

void GameApp::installAllegro()
{
	if (!al_init())
	{
		fprintf(stderr, "allegro init failed!\n");
	}

	//load image loader addon
	if (!al_init_image_addon())
	{
		fprintf(stderr, "image addon failed to load!\n");
	}

	//install audio stuff
	if (!al_install_audio())
	{
		fprintf(stderr, "failed to initialize sound!\n");
	}

	if (!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
	}

	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "failed to reserve samples!\n");
	}

	//should probably be done in the InputSystem!
	if (!al_install_keyboard())
	{
		printf("Keyboard not installed!\n");
	}

	//should probably be done in the InputSystem!
	if (!al_install_mouse())
	{
		printf("Mouse not installed!\n");
	}

	//should be somewhere else!
	al_init_font_addon();
	if (!al_init_ttf_addon())
	{
		printf("ttf font addon not initted properly!\n");
	}

	//actually load the font
	mpDefaultFont = al_load_ttf_font("cour.ttf", 20, 0);
	if (mpDefaultFont == NULL)
	{
		printf("ttf font file not loaded properly!\n");
	}

	if (!al_init_primitives_addon())
	{
		printf("Primitives addon not added!\n");
	}
}

void GameApp::startLoop()
{
	mLoopStartTime = mpLoopTimer->getElapsedTime();
}

bool GameApp::updateLoop()
{
	startLoop();

	float dt = getDeltaTime();

	mpMessageManager->processMessagesForThisframe();

	mpInputSystem->update();

	mpUnitManager->update(dt);

	draw();

	return endLoop();
}

void GameApp::draw()
{
	mpGraphicsSystem->getBackBuffer()->clear();

	//[draw things here]
	mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());

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

	if (mpLoopTimer != NULL)
	{
		delete mpLoopTimer;

		mpLoopTimer = NULL;
	}

	if (mpMessageManager != NULL)
	{
		delete mpMessageManager;

		mpMessageManager = NULL;
	}


	if (mpGraphicsSystem != NULL)
	{
		delete mpGraphicsSystem;

		mpGraphicsSystem = NULL;
	}

	if (mpGraphicsBufferManager != NULL)
	{
		delete mpGraphicsBufferManager;

		mpGraphicsBufferManager = NULL;
	}

	if (mpSpriteManager != NULL)
	{
		delete mpSpriteManager;

		mpSpriteManager = NULL;
	}

	if (mpInputSystem != NULL)
	{
		delete mpMessageManager;

		mpInputSystem = NULL;
	}
}


float GameApp::getDeltaTime()
{
	return mpLoopTimer->getElapsedTime() - mPrevFrameTime;
}


float GameApp::getCurrentTime()
{
	return mpLoopTimer->getElapsedTime();
}


void GameApp::quit()
{
	mContinueLoop = false;
}