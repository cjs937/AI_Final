#pragma once
#include "KinematicUnit.h"

class Timer;

class Explosion : public KinematicUnit
{
public:
	Explosion(KUInitData const & _data);
	~Explosion();

	virtual void update(float _dt) override;

private:

	Timer* mpTimer;

	void vanish();
};