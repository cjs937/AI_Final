#pragma once

#include "Game.h"
#include "Grid.h"
#include "Trackable.h"
#include <vector>

struct connectionNode
{
	bool isConnection;
	int gridIndex;
};

class HierarchicalPathfinding
{
public:
	HierarchicalPathfinding(int pixelWidth, int pixelHeight, int size);
	~HierarchicalPathfinding();

	void init();

	void update();

	void setNorth();
	void setSouth();
	void setEast();
	void setWest();

	bool getNorth();
	bool getSouth();
	bool getEast();
	bool getWest();

	void updateNorth();
	void updateSouth();
	void updateEast();
	void updateWest();

	bool getNearestConnection(std::vector<connectionNode*>);

	bool validateConnection(int currentTile);

	int getValueAtPosition(int x, int y);

private:
	std::vector<connectionNode*> mNorth;
	std::vector<connectionNode*> mSouth;
	std::vector<connectionNode*> mEast;
	std::vector<connectionNode*> mWest;

	int mGameWidth, mGameHeight, mTileSize;

};
