#pragma once
#include "Trackable.h"

class Spawner : public Trackable
{
public:
	Spawner() {};
	virtual ~Spawner() {};

	//Should be overridden by children
	virtual void update() {};
	virtual void spawnObject() = 0;
};