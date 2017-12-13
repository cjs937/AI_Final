#pragma once
#include "Spawner.h"

class PlayerSpawner : public Spawner
{
public:
	PlayerSpawner(Vector2D _position);

	~PlayerSpawner();

	virtual void spawnObject() override;
};