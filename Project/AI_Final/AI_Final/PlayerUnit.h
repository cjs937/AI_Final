#pragma once
#include "KinematicUnit.h"
#include "StateHandler.h"

class PlayerState;
class StateHandler;

class PlayerUnit : public KinematicUnit
{
	friend class PlayerState;

public:

	PlayerUnit(float _moveSpeed, KUInitData const & _data);

	~PlayerUnit();

	//Update override for kinematic unit (called by unit manager's update)
	//virtual void update(float _dt) override;

	void move( Vector2D const & _direction );

	void dropBomb();

	void applyPowerup(); // pass in powerup pointer when we have them

	void onHit();

	void die();

private:
	//StateHandler* mStateMachine;
	float mMoveSpeed;
	int mHealth;
};