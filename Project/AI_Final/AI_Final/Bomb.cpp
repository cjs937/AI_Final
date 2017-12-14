#include "Bomb.h"
#include "Defines.h"
#include "GameApp.h"
#include "Timer.h"
#include "RemoveUnitMessage.h"
#include "Grid.h"
#include "AssetLoader.h"

Bomb::Bomb(KUInitData const & _data) : KinematicUnit(_data)
{
	mpTimer = new Timer();

	mpTimer->start();
}

Bomb::~Bomb()
{
	if (mpTimer != NULL)
	{
		delete mpTimer;

		mpTimer = NULL;
	}
}

void Bomb::update(float _dt)
{
	KinematicUnit::update(_dt);

	//timer runs until bomb explodes
	if ( UNIT_MANAGER->getUnitData()->bombExplosionDelay <= mpTimer->getElapsedTime() * _dt )
		explode();
}


void Bomb::explode()
{
	std::vector<Vector2D> explosionPositions = getExplosionPositions();

	for (unsigned int i = 0; i < explosionPositions.size(); ++i)
	{
		UNIT_MANAGER->addUnit(EXPLOSION, explosionPositions[i], 0, Vector2D(0, 0), 0);
	}

	MESSAGE_MANAGER->addMessage(new RemoveUnitMessage(this), 0);
}



std::vector<Vector2D> Bomb::getExplosionPositions()
{
	std::vector<Vector2D> possiblePositions;
	Grid* grid = gpGameApp->getGrid();

	Vector2D unitPosition = getCenterPosition();

	int currentTileID = grid->getSquareIndexFromPixelXY(unitPosition.getX(), unitPosition.getY());

	//position of tile bomb was on
	Vector2D unitTilePosition = grid->getULCornerOfSquare(currentTileID);

	std::vector<int> adjacentIndicies = grid->getAdjacentIndices(currentTileID);

	//adds bomb's position first
	possiblePositions.push_back(unitTilePosition);

	//loops through the 4 directions
	for (unsigned int i = 0; i < adjacentIndicies.size(); ++i)
	{
		if (!gpGameApp->getAssetLoader()->checkIfCollisionNumber(adjacentIndicies[i]))
		{
			Vector2D position = grid->getULCornerOfSquare(adjacentIndicies[i]);

			possiblePositions.push_back(position);
		}
	}

	return possiblePositions;
}