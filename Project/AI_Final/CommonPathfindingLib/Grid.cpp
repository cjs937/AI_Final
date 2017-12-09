#include "Grid.h"
#include "GraphicsSystem.h"
#include "Vector2D.h"
#include <memory.h>
#include "Defines.h"
#include "Game.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

Grid::Grid( int pixelWidth, int pixelHeight, int squareSize )
:mPixelWidth(pixelWidth)
,mPixelHeight(pixelHeight)
,mSquareSize(squareSize)
{
	mGridWidth = pixelWidth / squareSize;
	mGridHeight = pixelHeight / squareSize;
	mpValues = new int[ mGridWidth * mGridHeight ];
	memset( mpValues, 0, sizeof(int) * mGridWidth * mGridHeight  );
}

Grid::~Grid()
{
	delete [] mpValues;
}

void Grid::draw(GraphicsBuffer* _backBuffer)
{
	Sprite* pBackgroundSprite = gpGame->getSpriteManager()->getSprite(BACKGROUND_SPRITE_ID);
	pBackgroundSprite->draw(*_backBuffer, 0, 0);
	int size = getGridWidth() * getGridHeight();

	//get any non-zero squares and make them desired sprites
	for (int i = 0; i < size; i++)
	{
		if (getValueAtIndex(i) != 0)
		{
			drawLevel(getULCornerOfSquare(i), gpGame->getSpriteManager()->getSprite(getValueAtIndex(i)), _backBuffer);
		}
	}
}

void Grid::drawLevel(Vector2D pos, Sprite* spriteToDraw, GraphicsBuffer* _backBuffer)
{
	spriteToDraw->drawScaled(*_backBuffer, pos.getX(), pos.getY(), getGridWidth(), getGridWidth(), 0);
}

int Grid::getSquareIndexFromPixelXY( int x, int y ) const
{
	x /= mSquareSize;
	y /= mSquareSize;
	return y * mGridWidth + x;
}

int Grid::getValueAtIndex( int index ) const
{
	if (index >= 0 && index < mGridWidth*mGridHeight)
	{
		return *(mpValues + index);
	}
	else
	{
		return CLEAR_VALUE;
	}
}

int Grid::getValueAtPixelXY( int x, int y ) const
{
	int index = getSquareIndexFromPixelXY( x, y );
	return getValueAtIndex( index );
}
	
void Grid::setValueAtIndex( int index, int value )
{
	if (index >= 0 && index < mGridWidth*mGridHeight)
	{
		*(mpValues + index) = value;
	}
}

void Grid::setValueAtPixelXY( int x, int y, int value )
{
	int index = getSquareIndexFromPixelXY( x, y );
	setValueAtIndex( index, value );
}

Vector2D Grid::getULCornerOfSquare( int index ) const
{
	int squareY = index / mGridWidth;
	int squareX = index % mGridWidth;
	Vector2D pos( (float)(squareX * mSquareSize), (float)(squareY * mSquareSize) );
	return pos;
}

//get adjacent grid square indices
std::vector<int> Grid::getAdjacentIndices( int theSquareIndex ) const
{
	std::vector<int> indices;

	//moded for 4 directions
	static const int NUM_DIRS = 4;
	//						        N  	E  	S	 W	
	static int xMods[NUM_DIRS] = {	0,	1,	0,	-1, };
	static int yMods[NUM_DIRS] = { -1,	0,	1,	 0,	};
	//find the x,y of the passed in index
	int x = theSquareIndex % mGridWidth;
	int y = theSquareIndex / mGridWidth;

	for( int i=0; i<NUM_DIRS; i++ )
	{
		//calc adjacent x,y
		int adjX = x + xMods[i];
		int adjY = y + yMods[i];

		//convert back to an index if on the Grid
		if( adjX >= 0 && adjX < mGridWidth && adjY >=0 && adjY < mGridHeight )
		{
			int adjIndex = ( adjY * mGridWidth ) + adjX;

			//add to vector of indices
			indices.push_back( adjIndex );
		}
	}
	return indices;
}


void Grid::save( std::ofstream& file )
{
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file << mpValues[i] << " ";
	}
}

void Grid::load( std::ifstream& file )
{
	int numSquares = mGridWidth * mGridHeight;
	for( int i=0; i<numSquares; i++ )
	{
		file >> mpValues[i];
	}
}
