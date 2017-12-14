#include "PlayerUnit.h"
#include "GridSteering.h"
#include "StateHandler.h"
#include "HitboxComponent.h"
#include "Sprite.h"
#include "Defines.h"
#include "GameApp.h"
#include "AssetLoader.h"
#include "SpriteManager.h"
#include "Sprite.h"

PlayerUnit::PlayerUnit(KUInitData const & _data):KinematicUnit(_data)
{
	mHealth = 3;

	mScore = 0;

	mPoweredUp = false;

	setSteering(new GridSteering(this));

	mpTimer = new Timer();

	int powerupSpriteID = gpGameApp->getAssetLoader()->getAssetIndex(INVINCIBLE_ID);

	mpPoweredUpSprite = gpGameApp->getSpriteManager()->getSprite(powerupSpriteID);

	mpTimer->start();
}

PlayerUnit::~PlayerUnit()
{
	if (mpTimer != NULL)
	{
		delete mpTimer;

		mpTimer = NULL;
	}
}


void PlayerUnit::update(float _dt)
{
	KinematicUnit::update(_dt);

	if (isPoweredUp())
		checkInvuln();
}

void PlayerUnit::draw(GraphicsBuffer* pBuffer)
{
	Sprite* toDraw;

	if (isPoweredUp())
	{
		toDraw = mpPoweredUpSprite;
	}
	else
	{
		toDraw = getSprite();
	}

	if (toDraw == NULL)
		return;

	toDraw->draw(*pBuffer, mPosition.getX(), mPosition.getY(), mOrientation);
}


void PlayerUnit::move(Vector2D const & _direction)
{
	Vector2D direction = _direction;

	static_cast<GridSteering*>(getSteering())->move(direction, UNIT_MANAGER->getUnitData()->playerSpeed);
}

void PlayerUnit::dropBomb()
{
	//if player's delay on bomb drop has passed
	if (UNIT_MANAGER->getUnitData()->playerBombDropDelay <= mpTimer->getElapsedTime())
	{
		UNIT_MANAGER->addUnit(BOMB, getPosition(), 0, Vector2D(0, 0), 0);

		mpTimer->start();
	}
}

void PlayerUnit::applyPowerup()
{
	mPoweredUp = true;

	mpTimer->start();

	DEBUG->log("on");
}

void PlayerUnit::disablePowerup()
{
	if (!isPoweredUp())
		return;

	mPoweredUp = false;

	mpTimer->stop();

	DEBUG->log("off");

}

void PlayerUnit::handleCollision(UnitType _colliderType)
{
	switch (_colliderType)
	{
	case (POWERUP):
	{
		applyPowerup();
	}
	default:
		break;
	}
}

void PlayerUnit::die()
{}

void PlayerUnit::checkInvuln()
{
	if (UNIT_MANAGER->getUnitData()->playerPowerupTime <= mpTimer->getElapsedTime() * gpGameApp->getDeltaTime())
	{
		disablePowerup();
	}
}
