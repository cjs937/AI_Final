#pragma once
#include "Trackable.h"

enum ComponentType
{
	INVALID_COMPONENT = -1,
	SAVEABLE,
	PAUSABLE,
	HITBOX
};


class Component : public Trackable
{
public:
	virtual ~Component() {};

	//Should be overridden if needed by children
	virtual void update(float _dt) {};
	virtual void draw() {};

	ComponentType getType() { return mType; };

protected:

	Component(ComponentType _type) :mType(_type) {};

	ComponentType mType;
};