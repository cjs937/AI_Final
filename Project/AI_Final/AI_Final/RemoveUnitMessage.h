#pragma once
#include "GameMessage.h"
#include "Defines.h"
#include "GameApp.h"

class RemoveUnitMessage : public GameMessage
{
public:
	RemoveUnitMessage(int _unitID) : GameMessage(REMOVE_UNIT), mUnitID(_unitID) {};
	~RemoveUnitMessage() {};

	virtual void process() override
	{
		UNIT_MANAGER->removeUnit(mUnitID);
	}

private:
	int mUnitID;
};