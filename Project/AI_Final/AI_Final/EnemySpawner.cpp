#include "EnemySpawner.h"
#include "Defines.h"
#include "GameApp.h"
#include "KinematicUnit.h"

EnemySpawner::EnemySpawner(Vector2D _position): Spawner(ENEMY_SPAWN, _position)
{}

EnemySpawner::~EnemySpawner()
{}

void EnemySpawner::spawnObject()
{
	if (!canSpawn())
		return;

	UNIT_MANAGER->addUnit(AI, getPosition(), 1.0f, Vector2D(0, 0), 0);
}

bool EnemySpawner::canSpawn()
{
	int numEnemies = UNIT_MANAGER->getUnitCount(AI);

	if (numEnemies < UNIT_MANAGER->getUnitData()->maxEnemies)
	{
		return true;
	}

	return false;
}
