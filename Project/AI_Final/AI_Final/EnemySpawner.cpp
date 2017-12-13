#include "EnemySpawner.h"
#include "Defines.h"
#include "GameApp.h"

EnemySpawner::EnemySpawner(Vector2D _position): Spawner(ENEMY_SPAWN, _position)
{}

EnemySpawner::~EnemySpawner()
{}

void EnemySpawner::spawnObject()
{
	UNIT_MANAGER->addUnit(AI, getPosition(), 1.0f, Vector2D(0, 0), 0);
}