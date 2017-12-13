#include "Pathfinder.h"
#include "Graph.h"
#include "Path.h"

Pathfinder::Pathfinder()
{

}
Pathfinder::Pathfinder(Graph* pGraph)
{
	mpGraph = pGraph;
}
/*
Pathfinder::Pathfinder(Graph* pGraph, Color _pathColor)
	:mpGraph(pGraph), mPathColor(_pathColor)
{
}*/

Pathfinder::~Pathfinder()
{
}