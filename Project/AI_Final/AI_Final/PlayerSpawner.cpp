#include "PlayerSpawner.h"
#include "GameApp.h"
#include "Defines.h"
#include "KinematicUnit.h"

PlayerSpawner::PlayerSpawner(Vector2D _position):Spawner(PLAYER_SPAWN, _position)
{}

PlayerSpawner::~PlayerSpawner()
{}

void PlayerSpawner::spawnObject()
{	
	if (!canSpawn())
		return;

	UNIT_MANAGER->addUnit(PLAYER, getPosition(), 1, Vector2D(), 0);
}

bool PlayerSpawner::canSpawn()
{
	//Player is a singleton, so if there is already one in the scene prevent another one from spawning
	if (UNIT_MANAGER->getPlayerUnit() != NULL)
	{
		return false;
	}

	return true;
}
