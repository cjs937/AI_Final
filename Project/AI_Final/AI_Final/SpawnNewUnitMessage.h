#pragma once
#include "GameMessage.h"
#include "Defines.h"
#include "GameApp.h"
#include "Spawner.h"
#include "SpawnSystem.h"
#include <vector>

class SpawnNewUnitMessage : public GameMessage
{
public:

	SpawnNewUnitMessage(SpawnerType _type) : GameMessage(SPAWN_ENEMY), mSpawnType(_type)
	{}

	~SpawnNewUnitMessage(){}

	virtual void process() override
	{
		std::vector<Spawner*> unitSpawners = UNIT_MANAGER->getSpawnSystem()->getSpawnersOfType(mSpawnType);

		if (unitSpawners.size() == 0)
			return;

		int randSpawner = rand() % unitSpawners.size();

		unitSpawners[randSpawner]->spawnObject();
	}

private:
	SpawnerType mSpawnType;
};