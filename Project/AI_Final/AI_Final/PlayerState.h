#pragma once
#include "State.h"

class PlayerUnit;

class PlayerState : public State
{
public:
	PlayerState(PlayerUnit & _player);
	~PlayerState();

	//Does nothing by default. If state needs collision input handles it
	virtual void handleCollision() {};

private:
	PlayerUnit* mPlayer;
};
