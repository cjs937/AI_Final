#include "Powerup.h"
#include "Defines.h"
#include "GameApp.h"
#include "RemoveUnitMessage.h"
#include "SpawnNewUnitMessage.h"
#include "Spawner.h"

Powerup::Powerup(KUInitData const & _data) :KinematicUnit(_data)
{}

Powerup::~Powerup()
{}

void Powerup::handleCollision(UnitType _collider)
{
	if (_collider == PLAYER)
	{
		MESSAGE_MANAGER->addMessage(new RemoveUnitMessage(this), 0);
		MESSAGE_MANAGER->addMessage(new SpawnNewUnitMessage(POWERUP_SPAWN), UNIT_MANAGER->getUnitData()->powerupRespawnTime);
	}
}