#include "UnitCollisionMessage.h"
#include "Defines.h"
#include "GameApp.h"
#include "KinematicUnit.h"

UnitCollisionMessage::UnitCollisionMessage(KinematicUnit* _unit, KinematicUnit* _collider): GameMessage(UNIT_COLLISION),
	mpUnit(_unit), mpCollider(_collider)
{}

UnitCollisionMessage::~UnitCollisionMessage()
{}

void UnitCollisionMessage::process()
{
	mpUnit->handleCollision(mpCollider->getType());
}