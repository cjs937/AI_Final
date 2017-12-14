#pragma once
#include "Spawner.h"

class EnemySpawner : public Spawner
{
public:
	EnemySpawner(Vector2D _position);

	~EnemySpawner();

	virtual void spawnObject() override;
	virtual bool canSpawn() override;

};