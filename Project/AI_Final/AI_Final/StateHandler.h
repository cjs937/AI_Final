#pragma once
#include "Trackable.h"

class State;

//State machine
class StateHandler : public Trackable
{
public:
	StateHandler();
	~StateHandler();

	virtual void update();
	void changeState(State* _newState, bool _exitState = true);

private:
	State* mCurrentState;
};