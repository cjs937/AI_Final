#pragma once
#include "GameMessage.h"
#include "Vector2D.h"
#include "GameApp.h"
#include "AIUnit.h"

class MovePlayerMessage : public GameMessage
{
public:

	MovePlayerMessage(Vector2D _direction) : GameMessage(MOVE_PLAYER), mDirection(_direction) {};
	~MovePlayerMessage() {};

	virtual void process() override
	{
		gpGameApp->test->moveTest(mDirection, 100);
	}

private:

	Vector2D mDirection;
};