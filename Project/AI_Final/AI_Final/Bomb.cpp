#include "Bomb.h"
#include "Defines.h"
#include "GameApp.h"
#include "Timer.h"
#include "RemoveUnitMessage.h"

Bomb::Bomb(KUInitData const & _data) : KinematicUnit(_data)
{
	mpTimer = new Timer();

	mpTimer->start();
}

Bomb::~Bomb()
{
	if (mpTimer != NULL)
	{
		delete mpTimer;

		mpTimer = NULL;
	}
}

void Bomb::update(float _dt)
{
	KinematicUnit::update(_dt);

	//timer runs until bomb explodes
	if ( UNIT_MANAGER->getUnitData()->bombExplosionDelay <= mpTimer->getElapsedTime() * _dt )
		explode();
}


void Bomb::explode()
{
	MESSAGE_MANAGER->addMessage(new RemoveUnitMessage(getID()), 0);
}