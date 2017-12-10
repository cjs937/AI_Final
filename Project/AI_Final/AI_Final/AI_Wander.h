#pragma once
#include "AIState.h"
#include <vector>

class AI_Wander : public AIState
{
protected:
	AI_Wander(AIUnit & _unit);
	~AI_Wander();

	virtual void onEnter() override;
	virtual State* update() override;

private:
	Vector2D mDirection;
	//returns array with possible directions to move in. _numDirections will hold the num indecies
	std::vector<Vector2D> getPossibleDirections(float _rayDistance);
	void wander();
};