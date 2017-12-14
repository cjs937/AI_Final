#pragma once
#include "GameMessage.h"
#include "Defines.h"
#include "GameApp.h"
#include "KinematicUnit.h"

class RemoveUnitMessage : public GameMessage
{
public:
	RemoveUnitMessage(KinematicUnit* _unit) : GameMessage(REMOVE_UNIT), mpUnit(_unit)
	{
		_unit->markForDeletion();
	};

	~RemoveUnitMessage() {};

	virtual void process() override
	{
		UNIT_MANAGER->removeUnit(mpUnit->getID());
	}

private:
	KinematicUnit* mpUnit;
};