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
#include "allegro5\allegro_primitives.h"

bool CollisionSystem::checkUnitCollision(KinematicUnit* _unit, Steering* _steering)
{
	Ray* ray = new Ray(_unit->getCenterPosition(), gpGameApp->getUnitManager()->getUnitData()->raycastDistance, _steering->getLinear());

	bool collided = rayCast(ray);

	delete ray;

	return collided;
}


bool CollisionSystem::rayCast(Ray* _ray)
{
	Grid* grid = gpGameApp->getGrid();

	Vector2D castPoint;

	for (float i = .1; i < 1.1f; i += .1)
	{
		castPoint = _ray->getPointAlongRay(i);

		int castValue = grid->getValueAtIndex(grid->getSquareIndexFromPixelXY(castPoint.getX(), castPoint.getY()));

		if (gpGameApp->getAssetLoader()->checkIfCollisionNumber(castValue))
		{
			return true;
		}
	}

	return false;

	//for (int i = 0; i < terrain.size(); ++i)
	//{
	//	currentTerrain = terrain[i];

	//	if (currentTerrain->getType() == BOX)
	//		collision = checkWallIntersection(_unit, terrain[i]);
	//	else if (currentTerrain->getType() == ELLIPSE)
	//		collision = checkEllipseIntersection(_unit, (EllipseTerrain*)terrainVector[i]);
	//	else
	//		collision = NULL;

	//	if (collision != NULL)
	//	{
	//		break;
	//	}
	//}

}
//
//RayCollision* CollisionSystem::checkWallIntersection(KinematicUnit* _unit, TerrainUnit* _wall)
//{
//	RayCollision* collision = NULL;
//	Vector2D* wallPoints = _wall->getAllPoints();
//	Ray* rayCast = new Ray(_unit->getPosition(), UNIT_RAYCAST_DISTANCE, _unit->getVelocity());
//
//	for (int i = 0; i < 4; ++i)// checks all sides of the wall
//	{
//		switch (i)
//		{
//		case 0:
//			collision = rayIntersectsSegment(rayCast, wallPoints[0], wallPoints[1]);
//			break;
//		case 1:
//			collision = rayIntersectsSegment(rayCast, wallPoints[0], wallPoints[2]);
//			break;
//		case 2:
//			collision = rayIntersectsSegment(rayCast, wallPoints[3], wallPoints[1]);
//			break;
//		case 3:
//			collision = rayIntersectsSegment(rayCast, wallPoints[3], wallPoints[2]);
//			break;
//		default:
//			collision = NULL;
//			break;
//		}
//
//		if (collision->hit)
//		{
//			break;
//		}
//
//		delete collision;
//
//		collision = NULL;
//	}
//
//	delete[] wallPoints;
//	delete rayCast;
//
//	return collision;
//
//}
//
//RayCollision* CollisionSystem::checkEllipseIntersection(KinematicUnit* _unit, EllipseTerrain* _ellipse)
//{
//	RayCollision* collision = NULL;
//	Ray* rayCast = new Ray(_unit->getPosition(), UNIT_RAYCAST_DISTANCE, _unit->getVelocity());
//
//	collision = rayIntersectsEllipse(rayCast, _ellipse->getPosition(), _ellipse->getRadius());
//
//	if (!collision->hit)
//	{
//		delete collision;
//
//		collision = NULL;
//	}
//
//	delete rayCast;
//
//	return collision;
//}
///*https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect*/
//RayCollision* CollisionSystem::rayIntersectsSegment(Ray* _ray, Vector2D _pointA, Vector2D _pointB)
//{
//	bool hit = false;
//	Vector2D collisionPoint = Vector2D();
//	//Ray = p + tr
//	//Wall(a, b) = a + t'd  
//	//d = (b - a)
//
//	Vector2D wall_d = _pointB - _pointA;
//
//	float rXd = Utility::crossProduct(_ray->getDirection(), wall_d);
//
//	if (rXd == 0)
//		hit = false;
//	else
//	{
//		//t = (a - p) x d / (r x d)
//		float t_ray = Utility::crossProduct((_pointA - _ray->getSourcePoint()), wall_d) / rXd;
//
//		//t' = (a - p) x r / ( r x d)
//		float t_wall = Utility::crossProduct((_pointA - _ray->getSourcePoint()), _ray->getDirection()) / Utility::crossProduct(_ray->getDirection(), wall_d);
//
//		//hit if r x s != 0 && 0 <= t <= 1 && 0 <= t' <= 1
//		hit = (Utility::crossProduct(_ray->getDirection(), wall_d) != 0.0f && 0.0f <= t_ray && t_ray <= 1.0f && 0.0f <= t_wall && t_wall <= 1.0f);
//
//		collisionPoint = hit ? _ray->getPointAlongRay(t_ray) :
//			Vector2D();
//	}
//
//	return new RayCollision(hit, collisionPoint);
//}