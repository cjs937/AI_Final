#include "GridSteering.h"
#include "CollisionSystem.h"

GridSteering::GridSteering()
{
	mApplyDirectly = true;
}

GridSteering::~GridSteering()
{}

void GridSteering::move(Vector2D const & _direction, float _speed)
{
	mSteeringThisFrame = _direction * _speed;
}

Steering* GridSteering::getSteering()
{
	setLinear(mSteeringThisFrame);

	//return steering to 0
	mSteeringThisFrame = Vector2D();

	return this;
}
