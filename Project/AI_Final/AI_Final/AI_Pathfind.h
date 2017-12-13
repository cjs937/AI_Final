#pragma once

#include "AIState.h"
#include <vector>
#include "GridPathfinder.h"

class Timer;

const float PATHFIND_DELAY = 2.0f;
const float MAX_DISTANCE = 1000;

class AI_Pathfind : public AIState
{
public:
	AI_Pathfind(AIUnit & _unit);
	~AI_Pathfind();

	virtual void onEnter() override;
	virtual State* update() override;

private:
	Vector2D mDirection;
	Path mPath;
	Node* mpToNode;

	int mTo, mFrom, currentIndexPos;

	void getPath();

	Vector2D getDirectionFromIndex(float _rayDistance);
	void move();


};