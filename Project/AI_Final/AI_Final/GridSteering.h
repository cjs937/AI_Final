#pragma once
#include "Steering.h"

class GridSteering : public Steering
{
public:
	GridSteering();
	~GridSteering();

	void move(Vector2D const & _direction, float _speed);

	virtual Steering* getSteering() override;

private:
	Vector2D mSteeringThisFrame;
};