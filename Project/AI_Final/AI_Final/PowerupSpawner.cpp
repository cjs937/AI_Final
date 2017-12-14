#include "PowerupSpawner.h"
#include "Defines.h"
#include "GameApp.h"
#include "KinematicUnit.h"

PowerupSpawner::PowerupSpawner(Vector2D _position):Spawner(POWERUP_SPAWN, _position)
{}

PowerupSpawner::~PowerupSpawner()
{}

void PowerupSpawner::spawnObject()
{
	if (!canSpawn())
		return;

	UNIT_MANAGER->addUnit(POWERUP, getPosition(), 0.0f, Vector2D(0, 0), 0);
}

bool PowerupSpawner::canSpawn()
{
	int numPowerups = UNIT_MANAGER->getUnitCount(POWERUP);

	if (numPowerups < UNIT_MANAGER->getUnitData()->maxCandies)
	{
		return true;
	}

	return false;
}