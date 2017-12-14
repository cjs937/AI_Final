#pragma once
#include "Spawner.h"

class PowerupSpawner : public Spawner
{
public:
	PowerupSpawner(Vector2D _position);
	~PowerupSpawner();

	virtual void spawnObject() override;
	virtual bool canSpawn() override;

};