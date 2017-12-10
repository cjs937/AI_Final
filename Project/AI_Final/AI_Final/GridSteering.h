#pragma once
#include "Steering.h"

class KinematicUnit;

class GridSteering : public Steering
{
public:
	GridSteering(KinematicUnit* _unit);
	~GridSteering();

	void move(Vector2D const & _direction, float _speed);

	virtual Steering* getSteering() override;

private:
	KinematicUnit* mpUnit;
	Vector2D mSteeringThisFrame;
};