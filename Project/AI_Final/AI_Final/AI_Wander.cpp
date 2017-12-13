#include "AI_Wander.h"
#include "Defines.h"
#include "Ray.h"
#include "CollisionSystem.h"
#include "AIUnit.h"
#include "GameApp.h"
#include "Timer.h"
#include "Grid.h"
#include "AssetLoader.h"

AI_Wander::AI_Wander(AIUnit & _unit):AIState(_unit)
{
	mpTimer = new Timer();
}
 
AI_Wander::~AI_Wander()
{
	if (mpTimer != NULL)
	{
		delete mpTimer;

		mpTimer = NULL;
	}
}

void AI_Wander::onEnter()
{
//	getWanderDirection();

	mpTimer->start();
}

State* AI_Wander::update()
{
	if(mpTimer->getElapsedTime() >= WANDER_DELAY)
		getWanderDirection();

	move();

	//should return null unless base behavior changes
	return AIState::update();
}

void AI_Wander::getWanderDirection()
{
	std::vector<Vector2D> possibleDirections = getPossibleDirections(UNIT_MANAGER->getUnitData()->raycastDistance);

	if (possibleDirections.size() <= 0)
	{
		DEBUG->log("No directions to move");

		return;
	}

	int randNum = rand() % possibleDirections.size();

	mDirection = possibleDirections[randNum];

	possibleDirections.clear();

	mpTimer->stop();

	mpTimer->start();
}


void AI_Wander::move()
{
	if (CollisionSystem::checkTerrainCollision(mUnit->getCenterPosition(), mDirection, UNIT_MANAGER->getUnitData()->raycastDistance))
	{
		mDirection = Vector2D(-mDirection.getX(), -mDirection.getY());
	}

	mUnit->move(mDirection, UNIT_MANAGER->getUnitData()->aiSpeed);
}


std::vector<Vector2D> AI_Wander::getPossibleDirections(float _rayDistance)
{				
	std::vector<Vector2D> possibleDirections;
	Vector2D unitPosition = mUnit->getCenterPosition();
	Grid* grid = gpGameApp->getGrid();
	int currentTileID = grid->getSquareIndexFromPixelXY(unitPosition.getX(), unitPosition.getY());

	std::vector<int> adjacentIndicies = grid->getAdjacentIndices(currentTileID);

	//loops through the 4 directions
	for (unsigned int i = 0; i < adjacentIndicies.size(); ++i)
	{
		if (!gpGameApp->getAssetLoader()->checkIfCollisionNumber(adjacentIndicies[i]))
		{
			Vector2D direction = getDirectionFromIndex(grid->getULCornerOfSquare(currentTileID), adjacentIndicies[i]);

			possibleDirections.push_back(direction);
		}
	}

	return possibleDirections;
}

Vector2D AI_Wander::getDirectionFromIndex(Vector2D _unitPosition, int _index)
{
	Vector2D squarePos = gpGameApp->getGrid()->getULCornerOfSquare(_index);

	Vector2D direction = (squarePos - _unitPosition);
	
	direction.normalize();

	return direction;
}

