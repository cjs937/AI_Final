#pragma once
#include "AIState.h"
#include <vector>

class Timer;

const float WANDER_DELAY = 2000.0f;
const float PATHFIND_DELAY = 8000.0f;

class AI_Wander : public AIState
{
public:
	AI_Wander(AIUnit & _unit);
	~AI_Wander();

	virtual void onEnter() override;
	virtual State* update() override;

private:
	Vector2D mDirection;
	Timer* mpTimer;
	Timer* mpSwitchOff;

	//returns array with possible directions to move in. _numDirections will hold the num indecies
	std::vector<Vector2D> getPossibleDirections(float _rayDistance);

	//gets the grid based direction ( (1,0), (0,1) etc.. ) of the index relative to the player's current  tile
	Vector2D getDirectionFromIndex(Vector2D _unitPosition, int _index);
	void getWanderDirection();
	void move();
};