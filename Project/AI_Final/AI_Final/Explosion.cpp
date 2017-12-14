#include "Explosion.h"
#include "Timer.h"
#include "Defines.h"
#include "GameApp.h"
#include "RemoveUnitMessage.h"

Explosion::Explosion(KUInitData const & _data) : KinematicUnit(_data)
{
	mpTimer = new Timer();

	mpTimer->start();
}

Explosion::~Explosion()
{
	if (mpTimer != NULL)
	{
		delete mpTimer;

		mpTimer = NULL;
	}
}

void Explosion::update(float _dt)
{
	KinematicUnit::update(_dt);

	//timer runs until bomb explodes
	if (UNIT_MANAGER->getUnitData()->explosionUptime <= mpTimer->getElapsedTime() * _dt)
		vanish();
}

void Explosion::vanish()
{
	MESSAGE_MANAGER->addMessage(new RemoveUnitMessage(this), 0);
}