#include <allegro5/allegro_primitives.h>
#include "LevelEditor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Grid.h"
#include "Vector2D.h"
#include "Editor.h"

LevelEditor::LevelEditor(Grid* pGrid)
	:mpGrid(pGrid)
	, mDirty(true)
{
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::refresh()
{
	const ALLEGRO_COLOR& color = BLACK_COLOR;
	if (mDirty)
	{
		//remove old entries first
		removeAllEntriesOfColor(color);

		int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
		//get any non-zero squares and send them to the visualizer
		for (int i = 0; i<size; i++)
		{
			if (mpGrid->getValueAtIndex(i) != 0)
			{
				//addColor(i, color);
			}
		}
	}
	mDirty = false;
}

void LevelEditor::addColor(int index, const ALLEGRO_COLOR& color)
{
	//Editor* pEditor = dynamic_cast<Editor*>(gpGame);
	//set dirty flag
	mDirty = true;

	//std::vector< Sprite*, std::vector<int> >::iterator iter = 

	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find(color);

	if (iter != mColormap.end())//found the existing entry
	{
		iter->second.push_back(index);
	}
	else
	{
		//create a vector to put in the map
		std::vector<int> colorVector;
		colorVector.push_back(index);

		//put the vector into the map
		mColormap[color] = colorVector;
	}
}

/*
void LevelEditor::addSprite(int index, const Sprite* sprite)
{
	//set dirty flag
	mDirty = true;
	
}*/

void LevelEditor::removeAllEntriesOfColor(const ALLEGRO_COLOR& color)
{
	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find(color);

	if (iter != mColormap.end())
	{
		mColormap.erase(iter);
	}
}


/*
void LevelEditor::removeAllEntriesOfSprite(const Sprite* sprite)
{
}*/

void LevelEditor::draw(GraphicsBuffer& dest)
{
	if (mDirty)
	{
		refresh();
	}

	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap(dest.getBitmap());

	int gridHeight = mpGrid->getGridHeight();
	int gridWidth = mpGrid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	int squareSize = mpGrid->getSquareSize();

	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter;
	for (iter = mColormap.begin(); iter != mColormap.end(); ++iter)
	{
		std::vector<int> theIndices = iter->second;

		for (unsigned int i = 0; i<theIndices.size(); i++)
		{
			Vector2D ulPos = mpGrid->getULCornerOfSquare(theIndices[i]);
			al_draw_filled_rectangle(ulPos.getX(), ulPos.getY(), ulPos.getX() + squareSize, ulPos.getY() + squareSize, iter->first);
			//mpBuffer->fillRegion( ulPos, Vector2D( ulPos.getX() + squareSize, ulPos.getY() + squareSize ), iter->first );
		}
	}

	GraphicsSystem::switchTargetBitmap(pOldTarget);
}


/*
void LevelEditor::refresh()
{
const ALLEGRO_COLOR& color = BLACK_COLOR;
if (mDirty)
{
//remove old entries first
removeAllEntriesOfColor(color);

int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
//get any non-zero squares and send them to the visualizer
for (int i = 0; i<size; i++)
{
if (mpGrid->getValueAtIndex(i) == 2)
{
addColor(i, color);
}
}
}
mDirty = false;
}

void LevelEditor::addColor(int index, const ALLEGRO_COLOR& color)
{
//set dirty flag
mDirty = true;

//find the existing entry in the map (if it exists)
std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find(color);

if (iter != mColormap.end())//found the existing entry
{
iter->second.push_back(index);
}
else
{
//create a vector to put in the map
std::vector<int> colorVector;
colorVector.push_back(index);

//put the vector into the map
mColormap[color] = colorVector;
}
}


void LevelEditor::addSprite(int index, const Sprite* sprite)
{
//set dirty flag
mDirty = true;

}

void LevelEditor::removeAllEntriesOfColor(const ALLEGRO_COLOR& color)
{
	//find the existing entry in the map (if it exists)
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter = mColormap.find(color);

	if (iter != mColormap.end())
	{
		mColormap.erase(iter);
	}
}



void LevelEditor::removeAllEntriesOfSprite(const Sprite* sprite)
{
}

void LevelEditor::draw(GraphicsBuffer& dest)
{
	if (mDirty)
	{
		refresh();
	}

	ALLEGRO_BITMAP* pOldTarget = GraphicsSystem::switchTargetBitmap(dest.getBitmap());

	int gridHeight = mpGrid->getGridHeight();
	int gridWidth = mpGrid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	int squareSize = mpGrid->getSquareSize();

	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare >::iterator iter;
	for (iter = mColormap.begin(); iter != mColormap.end(); ++iter)
	{
		std::vector<int> theIndices = iter->second;

		for (unsigned int i = 0; i<theIndices.size(); i++)
		{
			Vector2D ulPos = mpGrid->getULCornerOfSquare(theIndices[i]);
			al_draw_filled_rectangle(ulPos.getX(), ulPos.getY(), ulPos.getX() + squareSize, ulPos.getY() + squareSize, iter->first);
			//mpBuffer->fillRegion( ulPos, Vector2D( ulPos.getX() + squareSize, ulPos.getY() + squareSize ), iter->first );
		}
	}

	GraphicsSystem::switchTargetBitmap(pOldTarget);
}

*/
void LevelEditor::clear()
{
	mColormap.clear();
}