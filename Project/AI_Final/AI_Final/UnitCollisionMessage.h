#pragma once
#include "GameMessage.h"

class KinematicUnit;

class UnitCollisionMessage : public GameMessage
{
public:
	UnitCollisionMessage(KinematicUnit* _unit, KinematicUnit* _collider);
	~UnitCollisionMessage();

	virtual void process() override;

private:
	KinematicUnit* mpUnit;
	KinematicUnit* mpCollider;
};