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