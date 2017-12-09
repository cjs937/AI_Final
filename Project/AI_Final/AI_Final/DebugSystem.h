#pragma once
#include "Trackable.h"

class GraphicsBuffer;

class DebugSystem : public Trackable
{
public:
	DebugSystem();
	~DebugSystem();

	void update();
	void draw(GraphicsBuffer* const _backBuffer);

	void toggle();
	void toggle(bool _isOn);

	bool isActive() { return mIsActive; };

private:
	bool mIsActive;

	void drawPaths();

};