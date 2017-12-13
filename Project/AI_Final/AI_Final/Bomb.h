#pragma once
#include "KinematicUnit.h"

class Timer;


class Bomb : public KinematicUnit
{
public:
	Bomb(KUInitData const & _data);
	~Bomb();

	virtual void update(float _dt) override;

private:

	Timer* mpTimer;

	void explode();
};