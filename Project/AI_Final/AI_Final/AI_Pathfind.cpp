#include "AI_Pathfind.h"
#include "Defines.h"
#include "Ray.h"
#include "CollisionSystem.h"
#include "AIUnit.h"
#include "GameApp.h"
#include "Timer.h"
#include "Path.h"
#include "AssetLoader.h"
#include "PlayerUnit.h"
#include "AStarPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"
#include "AI_Wander.h"
#include "DebugLine.h"
#include "AI_SeekState.h"

AI_Pathfind::AI_Pathfind(AIUnit & _unit) : AIState (_unit)
{
}

AI_Pathfind::~AI_Pathfind()
{
}

void AI_Pathfind::onEnter()
{
	mResetCheck = 0;
	mTo = 0;
	mFrom = 0;
	currentIndexPos = 0;
	mpToNode = NULL;
	mPathFound = false;
}

State* AI_Pathfind::update()
{
	Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getCenterPosition();
	if ((playerPos - mUnit->getCenterPosition()).getLengthSquared() <= MAX_DISTANCE || mPath.getNumNodes() > 0)
	{
		if (mPath.getNumNodes() == 1)
		{
			//mPath.clear();
			mPathFound = false;
			return new AI_SeekState(*mUnit);
		}
		if (mPathFound == false)
		{
			getPath();
			mPathFound = true;
		}
		mDirection = getNextDirection();
		move();
	}
	else
	{
		//mPath.clear();
		mPathFound = false;
		return new AI_SeekState(*mUnit);

	}
	return AIState::update();
}

void AI_Pathfind::getPath()
{
	//dear God what have I created.
	mFrom = gpGameApp->getGrid()->getSquareIndexFromPixelXY(mUnit->getPosition().getX(), mUnit->getPosition().getY());
	mTo = gpGameApp->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getUnitManager()->getPlayerUnit()->getPosition().getX(), gpGameApp->getUnitManager()->getPlayerUnit()->getPosition().getY());
	
	mPath = gpGameApp->getPathfinder()->findPath(gpGameApp->getGridGraph()->getNode(mTo), gpGameApp->getGridGraph()->getNode(mFrom));
}
//if the plyer is on the next node of the path it will get the one after it, if
//the node was null it will get the first path node.
Vector2D AI_Pathfind::getNextDirection()
{
	Vector2D unitPosition = mUnit->getCenterPosition();
	Grid* grid = gpGameApp->getGrid();
	int currentTileID = grid->getSquareIndexFromPixelXY(unitPosition.getX(), unitPosition.getY());

	if (mpToNode == NULL)
		mpToNode = mPath.getAndRemoveNextNode();
	else if (currentTileID == mpToNode->getId())
	{
		mResetCheck++;
		if (currentTileID == mpToNode->getId())
			mpToNode = mPath.getAndRemoveNextNode();
	}
	//initialize and use to return direction
	Vector2D direction = getDirectionFromIndex(grid->getULCornerOfSquare(currentTileID), mpToNode->getId());
	std::cout << direction.getX() << "       " << direction.getY() << std::endl;
	
	return direction;
}

Vector2D AI_Pathfind::getDirectionFromIndex(Vector2D _unitPosition, int _index)
{
	Vector2D squarePos = gpGameApp->getGrid()->getULCornerOfSquare(_index);

	Vector2D direction = (squarePos - _unitPosition);

	direction.normalize();

	return direction;
}

void AI_Pathfind::move()
{
	if (CollisionSystem::checkTerrainCollision(mUnit->getCenterPosition(), mDirection, UNIT_MANAGER->getUnitData()->raycastDistance))
	{
		mDirection = Vector2D(-mDirection.getX(), -mDirection.getY());
	}
	
	mUnit->move(mDirection, UNIT_MANAGER->getUnitData()->aiSpeed);
}