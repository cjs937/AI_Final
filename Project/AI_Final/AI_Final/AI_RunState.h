#pragma once

#include "AIState.h"
#include <vector>

class AI_RunState : public AIState
{
public:
	AI_RunState(AIUnit & _unit);
	~AI_RunState();

	virtual void onEnter() override;
	virtual State* update() override;

private:
	Vector2D mDirection;
	void move();
};
