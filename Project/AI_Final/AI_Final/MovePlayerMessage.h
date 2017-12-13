#pragma once
#include "GameMessage.h"
#include "Vector2D.h"
#include "Defines.h"
#include "PlayerUnit.h"
#include "GameApp.h"

class MovePlayerMessage : public GameMessage
{
public:

	MovePlayerMessage(Vector2D _direction) : GameMessage(MOVE_PLAYER), mDirection(_direction) {};
	~MovePlayerMessage() {};

	virtual void process() override
	{
		PlayerUnit* player = UNIT_MANAGER->getPlayerUnit();

		if(player != NULL)
			player->move(mDirection);
	}

private:

	Vector2D mDirection;
};