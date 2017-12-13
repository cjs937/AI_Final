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


AI_Pathfind::AI_Pathfind(AIUnit & _unit)
{
}

AI_Pathfind::~AI_Pathfind()
{
}

void AI_Pathfind::onEnter()
{
	mTo = 0;
	mFrom = 0;
	currentIndexPos = 0;
	mpToNode = NULL;
}

State* AI_Pathfind::update()
{
	Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getCenterPosition();
	if ((gpGameApp->getUnitManager()->getPlayerUnit()->getCenterPosition()
		- mUnit->getCenterPosition()).getLengthSquared() <= MAX_DISTANCE)
	{
		if (mPath.getNumNodes() <= 0)
			getPath();

		mDirection = getDirectionFromIndex(0.0);
	}
	return AIState::update();
}

void AI_Pathfind::getPath()
{
	//dear God what have I created.
	mFrom = gpGameApp->getGrid()->getSquareIndexFromPixelXY(mUnit->getCenterPosition().getX(), mUnit->getCenterPosition().getY());
	mTo = gpGameApp->getGrid()->getSquareIndexFromPixelXY(gpGameApp->getUnitManager()->getPlayerUnit()->getCenterPosition().getX(), gpGameApp->getUnitManager()->getPlayerUnit()->getCenterPosition().getY());
	
	mPath = gpGameApp->getPathfinder()->findPath(gpGameApp->getGridGraph()->getNode(mFrom), gpGameApp->getGridGraph()->getNode(mTo));
}
//if the plyer is on the next node of the path it will get the one after it, if
//the node was null it will get the first path node.
Vector2D AI_Pathfind::getDirectionFromIndex(float _rayDistance)
{
	Vector2D unitPosition = mUnit->getCenterPosition();
	Grid* grid = gpGameApp->getGrid();
	int currentTileID = grid->getSquareIndexFromPixelXY(unitPosition.getX(), unitPosition.getY());

	if (mpToNode == NULL)
		mpToNode = mPath.getAndRemoveNextNode();
	else 
		if (currentTileID == mpToNode->getId())
				mpToNode = mPath.getAndRemoveNextNode();
	//initialize and use to return direction
	Vector2D squarePos = gpGameApp->getGrid()->getULCornerOfSquare(mpToNode->getId());
	Vector2D direction = (squarePos - grid->getULCornerOfSquare(currentTileID));
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

