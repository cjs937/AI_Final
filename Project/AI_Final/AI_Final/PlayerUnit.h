#pragma once
#include "KinematicUnit.h"
#include "StateHandler.h"

enum UnitType;
class PlayerState;
class StateHandler;
class Timer;

class PlayerUnit : public KinematicUnit
{
	friend class PlayerState;

public:

	PlayerUnit(KUInitData const & _data);

	~PlayerUnit();

	//Update override for kinematic unit (called by unit manager's update)
	//virtual void update(float _dt) override;

	void move( Vector2D const & _direction );

	void dropBomb();

	void applyPowerup(); // pass in powerup pointer when we have them

	virtual void handleCollision(UnitType _colliderType) override;

	void die();

private:
	//StateHandler* mStateMachine;
	Timer* mpTimer;
	float mBombDropDelay;
	float mMoveSpeed;
	int mHealth;
	int mScore;
	bool mPoweredUp;
};