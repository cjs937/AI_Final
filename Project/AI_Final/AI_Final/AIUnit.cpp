#include "AIUnit.h"
#include "GridSteering.h"
#include "StateHandler.h"
#include "AI_Wander.h"
#include "Defines.h"
#include "GameApp.h"
#include "RemoveUnitMessage.h"
#include "SpawnNewUnitMessage.h"
#include "Spawner.h"
#include "PlayerUnit.h"

AIUnit::AIUnit(KUInitData const & _data) : KinematicUnit(_data)
{
	setSteering(new GridSteering(this));

	StateHandler* stateHandler = new StateHandler();
	AI_Wander* newState = new AI_Wander(*this);

	stateHandler->changeState(*newState);

	addComponent(stateHandler);
}

AIUnit::~AIUnit() 
{}

void AIUnit::move(Vector2D _direction, float _ms)
{
	static_cast<GridSteering*>(getSteering())->move(_direction, _ms);
}

void AIUnit::handleCollision(UnitType _colliderType)
{
	if (_colliderType == EXPLOSION)
	{
		die();
	}
	else if (_colliderType == PLAYER)
	{
		if (UNIT_MANAGER->getPlayerUnit()->isPoweredUp())
			die();
	}
}

void AIUnit::die()
{
	//spawn coin at position

	MESSAGE_MANAGER->addMessage(new RemoveUnitMessage(this), 0);

	MESSAGE_MANAGER->addMessage(new SpawnNewUnitMessage(ENEMY_SPAWN), UNIT_MANAGER->getUnitData()->enemyRespawnTime);
}
