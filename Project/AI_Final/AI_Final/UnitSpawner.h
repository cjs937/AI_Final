#pragma once/*
#include "UnitManager.h"
#include "GameApp.h"
class UnitSpawner
{
public:
	UnitSpawner(UnitType myType, Vector2D spawnLocation, float orientation, Vector2D velocity, float rotationVel, float spawnTime);
	~UnitSpawner();

private:
	float respawnTimer, respawnStart;
	bool isSpawned;
};

UnitSpawner::UnitSpawner(UnitType myType, Vector2D spawnLocation, float orientation, Vector2D velocity, float rotationVel, float spawnTime)
{
	gpGameApp->getUnitManager()->addUnit(myType, spawnLocation, orientation, velocity, rotationVel, spawnTime);
}

UnitSpawner::~UnitSpawner()
{
}*/