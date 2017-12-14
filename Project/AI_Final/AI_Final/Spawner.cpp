#include "Spawner.h"
#include "Timer.h"
#include "GameApp.h"

Spawner::Spawner(SpawnerType _type, Vector2D _position, bool _spawnOnStart) :
	mType(_type), mPosition(_position), mSpawnOnStart(_spawnOnStart)
{
	mpTimer = new Timer();
}

Spawner::~Spawner() 
{
	if (mpTimer != NULL)
	{
		delete mpTimer;

		mpTimer = NULL;
	}
}


//Should be overridden by children
void Spawner::update() 
{
	if (mDelaying)
	{
		if (mpTimer->getElapsedTime() * gpGameApp->getDeltaTime() >= mCurrentSpawnDelay)
		{
			mpTimer->stop();

			mDelaying = false;

			spawnObject();
		}
	}
}

void Spawner::spawnDelayedObject(float _delay)
{
	mDelaying = true;

	mCurrentSpawnDelay = _delay;

	mpTimer->start();
}