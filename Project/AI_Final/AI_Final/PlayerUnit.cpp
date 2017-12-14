#include "PlayerUnit.h"
#include "GridSteering.h"
#include "StateHandler.h"
#include "HitboxComponent.h"
#include "Sprite.h"
#include "Defines.h"
#include "GameApp.h"

PlayerUnit::PlayerUnit(KUInitData const & _data):KinematicUnit(_data)
{
	mHealth = 3;

	mScore = 0;

	mPoweredUp = false;

	setSteering(new GridSteering(this));

	mpTimer = new Timer();

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
