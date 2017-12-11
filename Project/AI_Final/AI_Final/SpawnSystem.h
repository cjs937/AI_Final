#pragma once
/**/
#include "GameApp.h"
#include "Trackable.h"
#include "KinematicUnit.h"
#include "UnitSpawner.h"
#include "UnitManager.h"

#include <vector>
#include "Vector2D.h"


class SpawnSystem : public Trackable
{
public:
	SpawnSystem();
	~SpawnSystem();

	void update(float dt);
	void addSpawnUnit(UnitType myType, Vector2D spawnLocation, float orientation, Vector2D velocity, float rotationVel, float spawnTime);

private:
	std::vector<UnitSpawner*> mpUnitsSpawned;
};

SpawnSystem::SpawnSystem()
{
}

SpawnSystem::~SpawnSystem()
{
}

//update each unit spawner
void SpawnSystem::update(float dt)
{
	for (int i = 0; i < mpUnitsSpawned.size(); ++i)
	{
		mpUnitsSpawned.at(i)->update(dt);
	}
}

void SpawnSystem::addSpawnUnit(UnitType myType, Vector2D spawnLocation, float orientation, Vector2D velocity, float rotationVel, float spawnTime)
{
	mpUnitsSpawned.push_back(new UnitSpawner(UnitType myType, Vector2D spawnLocation, float orientation, Vector2D velocity, float rotationVel, float spawnTime));
}*/