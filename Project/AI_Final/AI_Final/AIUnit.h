#pragma once
#include "KinematicUnit.h"
#include "GridSteering.h"

class AIUnit : public KinematicUnit
{
public:
	AIUnit(KUInitData const & _data);
	virtual ~AIUnit();

	void moveTest(Vector2D _direction, float _ms)
	{
		static_cast<GridSteering*>(getSteering())->move(_direction, _ms);
	}

private:
};