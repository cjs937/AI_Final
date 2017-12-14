#pragma once
#include "KinematicUnit.h"

class AIUnit : public KinematicUnit
{
public:
	AIUnit(KUInitData const & _data);
	virtual ~AIUnit();

	void move(Vector2D _direction, float _ms);

	virtual void handleCollision(UnitType _colliderType) override;

private:
	void die();
};