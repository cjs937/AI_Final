#pragma once

#include "GameApp.h"
#include "Trackable.h"
#include "KinematicUnit.h"
#include "UnitSpawner.h"
#include "UnitManager.h"

#include <vector>
#include "Vector2D.h"
#include "Grid.h"

enum SpawnerType;
class Spawner;

class SpawnSystem : public Trackable
{
public:
	SpawnSystem();
	~SpawnSystem();

	void initSpawners(Grid* _grid);
	void update(float dt);
	void addSpawner(Spawner* _spawner);
	std::vector<Spawner*> getSpawnersOfType(SpawnerType _type);

private:
	void clear();
	std::vector<Spawner*> mSpawners;
};