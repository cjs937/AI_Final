#include "Spawner.h"
#include "Timer.h"

Spawner::Spawner(SpawnerType _type, Vector2D _position, bool _spawnOnStart) :
	mType(_type), mPosition(_position), mSpawnOnStart(_spawnOnStart)
{
	mpTimer = new Timer();
}

Spawner::~Spawner() 
{}


//Should be overridden by children
void Spawner::update() 
{
	if (mDelaying)
	{
		if (mpTimer->getElapsedTime() >= mCurrentSpawnDelay)
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