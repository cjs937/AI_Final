#include "GridSteering.h"
#include "CollisionSystem.h"

GridSteering::GridSteering(KinematicUnit* _unit): mpUnit(_unit)
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

	//if collision, stop movement this frame
	if (CollisionSystem::checkTerrainCollision(mpUnit, this))
		setLinear(Vector2D());

	//return steering to 0
	mSteeringThisFrame = Vector2D();

	return this;
}
