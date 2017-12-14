#include "AI_Wander.h"
#include "Defines.h"
#include "Ray.h"
#include "CollisionSystem.h"
#include "AIUnit.h"
#include "GameApp.h"
#include "Timer.h"
#include "Grid.h"
#include "AssetLoader.h"
#include "AI_Pathfind.h"
#include "AI_SeekState.h"
#include "PlayerUnit.h"
AI_SeekState::AI_SeekState(AIUnit & _unit) :AIState(_unit)
{

}

AI_SeekState::~AI_SeekState()
{

}

void AI_SeekState::onEnter()
{

}

State* AI_SeekState::update()
{
	Vector2D playerPos = UNIT_MANAGER->getPlayerUnit()->getCenterPosition();

	if (!CollisionSystem::checkTerrainCollision(mUnit->getCenterPosition(), playerPos - mUnit->getCenterPosition(),
		(playerPos - mUnit->getCenterPosition()).getLength()) && UNIT_MANAGER->getPlayerUnit()->)
	{
		mDirection = playerPos - mUnit->getCenterPosition();
		mDirection.normalize();
	}
	else
		return new AI_Wander(*mUnit);

	move();

	//should return null unless base behavior changes
	return AIState::update();
}

void AI_SeekState::move()
{
	if (CollisionSystem::checkTerrainCollision(mUnit->getCenterPosition(), mDirection, UNIT_MANAGER->getUnitData()->raycastDistance))
	{
		mDirection = Vector2D(-mDirection.getX(), -mDirection.getY());
	}

	mUnit->move(mDirection, UNIT_MANAGER->getUnitData()->aiSpeed);
}