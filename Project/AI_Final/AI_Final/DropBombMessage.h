#pragma once
#include "GameMessage.h"
#include "PlayerUnit.h"
#include "GameApp.h"
#include "Defines.h"

class DropBombMessage : public GameMessage
{
public:
	DropBombMessage():GameMessage(DROP_BOMB) {};
	~DropBombMessage() {}

	virtual void process() override
	{
		UNIT_MANAGER->getPlayerUnit()->dropBomb();
	}
};