#pragma once
#include "Component.h"

class State;

//State machine
class StateHandler : public Component
{
public:
	StateHandler();
	~StateHandler();

	virtual void update() override;
	void changeState(State & _newState, bool _exitCurrentState = true);

private:
	State* mCurrentState;
};