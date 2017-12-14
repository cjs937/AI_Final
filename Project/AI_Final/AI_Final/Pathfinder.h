#pragma once

enum PathfinderType
{
	NONER = -1,
	DIJKSTRA,
	ASTAR
};

#include <vector>
#include <Trackable.h>
#include "Path.h"
#include "Color.h"

class Graph;
class Node;
class GraphicsBuffer;
class Grid;

#define VISUALIZE_PATH 1

class Pathfinder :public Trackable
{
public:
	Pathfinder();
	Pathfinder(Graph* pGraph);
	//Pathfinder(Graph* pGraph, Color _pathColor = Color(BLACK));
	virtual ~Pathfinder();

	virtual const Path& findPath(Node* pFrom, Node* pTo) = 0;

	virtual PathfinderType getType() { return NONER; };

	Path getPath() { return mPath; };

protected:
	Graph* mpGraph;
	Path mPath;  //cached version of the calculated path
};