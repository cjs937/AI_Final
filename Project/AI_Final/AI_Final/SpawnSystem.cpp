#include "SpawnSystem.h"
#include "Spawner.h"
#include "Grid.h"
#include "AssetLoader.h"
#include "PlayerSpawner.h"
#include "EnemySpawner.h"

SpawnSystem::SpawnSystem()
{}

SpawnSystem::~SpawnSystem()
{
	clear();
}

void SpawnSystem::clear()
{
	for (unsigned int i = 0; i < mSpawners.size(); ++i)
	{
		delete mSpawners[i];

		mSpawners[i] = NULL;
	}
}

void SpawnSystem::initSpawners(Grid* _grid)
{
	int size = _grid->getGridWidth() * _grid->getGridHeight();
	int playerSpawnIndex = gpGameApp->getAssetLoader()->getAssetIndex("playerSpawn");
	int enemySpawnIndex = gpGameApp->getAssetLoader()->getAssetIndex("enemySpawn");

	//get any non-zero squares and make them desired sprites
	for (int i = 0; i < size; i++)
	{
		int indexValue = _grid->getValueAtIndex(i);

		Spawner* newSpawner;

		if(indexValue == playerSpawnIndex)
		{
			newSpawner = new PlayerSpawner(_grid->getULCornerOfSquare(i));
		}
		else if (indexValue == enemySpawnIndex)
		{
			newSpawner = new EnemySpawner(_grid->getULCornerOfSquare(i));
		}
		else
		{
			continue;
		}

		addSpawner(newSpawner);

		if (newSpawner->spawnOnStart())
			newSpawner->spawnObject();

		//sets sprite at index to clear sprite
		_grid->setValueAtIndex(i, 0);
	}	
}

//update each unit spawner
void SpawnSystem::update(float dt)
{
	for (unsigned int i = 0; i < mSpawners.size(); ++i)
	{
		mSpawners[i]->update();
	}
}

void SpawnSystem::addSpawner(Spawner* _spawner)
{
	mSpawners.push_back(_spawner);
}

std::vector<Spawner*> SpawnSystem::getSpawnersOfType(SpawnerType _type)
{
	std::vector<Spawner*> spawnersToReturn;

	for (unsigned int i = 0; i < mSpawners.size(); ++i)
	{
		if (mSpawners[i]->getType() == _type)
			spawnersToReturn.push_back(mSpawners[i]);
	}

	return spawnersToReturn;
}
