#pragma once

#include "AIState.h"
#include <vector>

class AI_SeekState : public AIState
{
public:
	AI_SeekState(AIUnit & _unit);
	~AI_SeekState();

	virtual void onEnter() override;
	virtual State* update() override;

private:
	Vector2D mDirection;
	void move();
};