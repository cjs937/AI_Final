#include "Pathfinder.h"
#include "Graph.h"
#include "Path.h"
#include "Color.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::Pathfinder(Graph* pGraph)
{
	mpGraph = pGraph;
}

Pathfinder::~Pathfinder()
{
}