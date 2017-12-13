#pragma once

#include "Pathfinder.h"
class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder :public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder();
	GridPathfinder(GridGraph* pGraph);
	//GridPathfinder(GridGraph* pGraph, Color _pathColor = Color(BLACK));
	virtual ~GridPathfinder();

	virtual const Path& findPath(Node* pFrom, Node* pTo) = 0;

#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization(Grid* pGrid, GraphicsBuffer* pDest);
protected:
	std::vector<Node*> mVisitedNodes;
	GridVisualizer* mpVisualizer;
#endif

	double mTimeElapsed;
};