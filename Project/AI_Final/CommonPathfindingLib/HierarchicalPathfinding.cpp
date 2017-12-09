
#include "HierarchicalPathfinding.h"


HierarchicalPathfinding::HierarchicalPathfinding(int pixelWidth, int pixelHeight, int size)
{
	mGameWidth = pixelWidth;
	mGameHeight = pixelHeight;
	mTileSize = size;
}

HierarchicalPathfinding::~HierarchicalPathfinding()
{
	for each (connectionNode* segment in mNorth)
		delete segment;
	mNorth.clear();

	for each (connectionNode* segment in mSouth)
		delete segment;
	mSouth.clear();

	for each (connectionNode* segment in mEast)
		delete segment;
	mEast.clear();

	for each (connectionNode* segment in mWest)
		delete segment;
	mWest.clear();
}

void HierarchicalPathfinding::init()
{
	setNorth();
	setSouth();
	setEast();
	setWest();
}

void HierarchicalPathfinding::update()
{
	updateNorth();
	updateSouth();
	updateEast();
	updateWest();
}

int HierarchicalPathfinding::getValueAtPosition(int x, int y)
{
	return 
}

void HierarchicalPathfinding::setNorth()
{
	int startWidth = mGameWidth / 2;
	int startHeight = 0;
	int endHeight = mGameHeight / 2;

	while (startHeight != endHeight)
	{
		getValueAtPosition(startWidth, startHeight);
	}
}

void HierarchicalPathfinding::setSouth()
{

}

void HierarchicalPathfinding::setEast()
{

}

void HierarchicalPathfinding::setWest()
{

}

bool HierarchicalPathfinding::getNorth()
{

}

bool HierarchicalPathfinding::getSouth()
{

}

bool HierarchicalPathfinding::getEast()
{

}

bool HierarchicalPathfinding::getWest()
{

}

void HierarchicalPathfinding::updateNorth()
{

}

void HierarchicalPathfinding::updateSouth()
{

}

void HierarchicalPathfinding::updateEast()
{

}

void HierarchicalPathfinding::updateWest()
{

}

bool HierarchicalPathfinding::getNearestConnection(std::vector<connectionNode*>)
{

}

bool HierarchicalPathfinding::validateConnection(int currentTile)
{

}