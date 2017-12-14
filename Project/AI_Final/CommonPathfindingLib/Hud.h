#pragma once

#include "Trackable.h"
class GraphicsBuffer;
class Hud : public Trackable
{
public:
	Hud() {};
	virtual ~Hud() {}
	virtual void update(int var, GraphicsBuffer* _buffer) = 0;

private:

};
