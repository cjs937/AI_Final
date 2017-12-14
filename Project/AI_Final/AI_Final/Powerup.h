#pragma once
#include "KinematicUnit.h"

class Powerup : public KinematicUnit
{
public:
	Powerup(KUInitData const & _data);
	~Powerup();

	virtual void handleCollision(UnitType _collider) override;
};