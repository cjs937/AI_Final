#include "PlayerUnit.h"
#include "GridSteering.h"
#include "StateHandler.h"
#include "HitboxComponent.h"

PlayerUnit::PlayerUnit(float _moveSpeed, KUInitData const & _data):KinematicUnit(_data)
{
	addComponent(new StateHandler());
	//addComponent(new HitboxComponent())

	mMoveSpeed = _moveSpeed;
	mHealth = 3;

	setSteering(new GridSteering());
}

PlayerUnit::~PlayerUnit()
{}

//void PlayerUnit::update(float _dt)
//{
//	KinematicUnit::update(_dt);
//}

void PlayerUnit::move(Vector2D const & _direction)
{
	static_cast<GridSteering*>(getSteering())->move(_direction, mMoveSpeed);
}

void PlayerUnit::dropBomb()
{}

void PlayerUnit::applyPowerup()
{}// pass in powerup pointer when we have them

void PlayerUnit::onHit()
{}

void PlayerUnit::die()
{}