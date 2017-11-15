#pragma once
#include "Trackable.h"

class State : public Trackable
{
public:
	State() {};
	virtual ~State() {};

	//Override what is needed. All states need an update at least
	virtual void onEnter() {};
	//Update function should return next state to change to, or null if a change is not needed
	virtual State* update() = 0;
	virtual void onExit() {};
};