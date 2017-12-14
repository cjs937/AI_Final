#pragma once
#include "GameMessage.h"
#include "Defines.h"
#include "GameApp.h"
#include "Spawner.h"
#include "SpawnSystem.h"
#include <vector>
class SpawnNewEnemyMessage : public GameMessage
{
public:
	SpawnNewEnemyMessage() :GameMessage(SPAWN_ENEMY){}

	~SpawnNewEnemyMessage(){}

	virtual void process() override
	{
		std::vector<Spawner*> enemySpawners = UNIT_MANAGER->getSpawnSystem()->getSpawnersOfType(ENEMY_SPAWN);

		if (enemySpawners.size() == 0)
			return;

		int randSpawner = rand() % enemySpawners.size();

		enemySpawners[randSpawner]->spawnDelayedObject(UNIT_MANAGER->getUnitData()->enemyRespawnTime);
	}
};