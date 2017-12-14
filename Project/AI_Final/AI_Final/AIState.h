#pragma once
#include "State.h"
#include "AIUnit.h"

class AIState : public State
{
protected:
	AIUnit* mUnit;

	AIState() {};
	AIState(AIUnit & _unit) :mUnit(&_unit) {};
	~AIState() {};

	//Does nothing by default. If state needs collision input this handles it
	virtual void handleCollision() {};

	virtual State* update() override { return NULL; };

};