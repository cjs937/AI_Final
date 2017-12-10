#include "AI_Wander.h"
#include "Ray.h"
#include "CollisionSystem.h"
#include "AIUnit.h"
#include "GameApp.h"
#include "UnitManager.h"
#include "DebugSystem.h"

AI_Wander::AI_Wander(AIUnit & _unit):AIState(_unit)
{}

AI_Wander::~AI_Wander()
{}

void AI_Wander::onEnter()
{
	//generate random number between 1 - 4
	int randNum = rand() % 4 + 1;
}

State* AI_Wander::update()
{
	wander();
}

void AI_Wander::wander()
{
	std::vector<Vector2D> possibleDirections = getPossibleDirections(gpGameApp->getUnitManager()->getUnitData()->raycastDistance);

	if (possibleDirections.size <= 0)
	{
		gpGameApp->getDebugSystem()->log("No directions to move");

		return;
	}


}


std::vector<Vector2D> AI_Wander::getPossibleDirections(float _rayDistance)
{				
							/* right             up               left            down*/
	Vector2D* directions = new Vector2D[4]{ Vector2D(1,0), Vector2D(0,1), Vector2D(-1, 0), Vector2D(0, -1) };
	std::vector<Vector2D> possibleDirections;
	Vector2D unitPosition = mUnit->getCenterPosition();
	Ray* ray;

	//loops through the 4 directions
	for (int i = 0; i < 4; ++i)
	{
		ray = new Ray(unitPosition, _rayDistance, directions[i]);

		//if there was no collision at ray cast in that direction adds to vector
		if (!CollisionSystem::checkTerrainCollision(ray))
		{
			possibleDirections.push_back(directions[i]);
		}

		delete ray;

		ray = NULL;
	}

	return possibleDirections;
}
