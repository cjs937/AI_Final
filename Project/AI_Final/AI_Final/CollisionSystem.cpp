#include "CollisionSystem.h"
#include "KinematicUnit.h"
#include "UnitManager.h"
#include "GameApp.h"
#include "Steering.h"
#include <vector>
#include "Ray.h"
#include "Utility.h"
#include "Grid.h"
#include "AssetLoader.h"
#include "DebugSystem.h"
#include "DebugLine.h"
#include <map>
#include "HitboxComponent.h"
#include "UnitCollisionMessage.h"

bool CollisionSystem::checkTerrainCollision(Vector2D _start, Vector2D _direction, float _castDistance)
{
	Ray* ray = new Ray(_start, _castDistance, _direction);

	bool collided = checkTerrainCollision(ray);

	delete ray;

	return collided;
}


bool CollisionSystem::checkTerrainCollision(KinematicUnit* _unit, Steering* _steering)
{
	bool collided = checkTerrainCollision(_unit->getCenterPosition(), _steering->getLinear(), gpGameApp->getUnitManager()->getUnitData()->raycastDistance);

	return collided;
}

//Ray needs to be deleted outside this function
bool CollisionSystem::checkTerrainCollision(Ray* _ray)
{
	bool collided = rayCast(_ray);
															// if there was collision draws red ray, else draws green
	gpGameApp->getDebugSystem()->drawRequest(new DebugLine(_ray, (collided ? Color(RED) : Color(GREEN))));

	return collided;
}

void CollisionSystem::checkAllUnitCollisions()
{
	std::map<UnitType, std::map<IDType, KinematicUnit*>*> unitMap = UNIT_MANAGER->getMapList();
	//std::vector<std::pair<int, int>> completedChecks;

	for (auto i = unitMap.begin(); i != unitMap.end(); ++i)
	{
		std::map<IDType, KinematicUnit*>* currentMap = i->second;

		for (auto j = currentMap->begin(); j != currentMap->end(); ++j)
		{
			//If unit is marked for deletion
			if (j->second->isDeleting())
				continue;

			checkCollisions(j->second);
		}
	}

}

void CollisionSystem::checkCollisions(KinematicUnit* _unit)
{
	HitboxComponent* unitBox = dynamic_cast<HitboxComponent*>(_unit->getComponent(HITBOX));

	if (unitBox == NULL)
		return;

	std::map<UnitType, std::map<IDType, KinematicUnit*>*> unitMap = UNIT_MANAGER->getMapList();

	for (auto i = unitMap.begin(); i != unitMap.end(); ++i)
	{
		std::map<IDType, KinematicUnit*>* currentMap = i->second;

		for (auto otherUnit = currentMap->begin(); otherUnit != currentMap->end(); ++otherUnit)
		{
			if (otherUnit->second == _unit)
				continue;

			HitboxComponent* otherBox = dynamic_cast<HitboxComponent*>(otherUnit->second->getComponent(HITBOX));

			if (unitBox->checkCollision(otherBox))
			{
				MESSAGE_MANAGER->addMessage(new UnitCollisionMessage(_unit, otherUnit->second), 0);
			}
		}
	}
}


bool CollisionSystem::rayCast(Ray* _ray)
{
	Grid* grid = gpGameApp->getGrid();

	Vector2D castPoint;

	for (float i = .1; i < 1.1f; i += .3)
	{
		castPoint = _ray->getPointAlongRay(i);

		int castValue = grid->getValueAtIndex(grid->getSquareIndexFromPixelXY(castPoint.getX(), castPoint.getY()));

		if (gpGameApp->getAssetLoader()->checkIfCollisionNumber(castValue))
		{
			return true;
		}
	}

	return false;
}