#include "DebugSystem.h"

DebugSystem::DebugSystem()
{
	toggle(false);
}

DebugSystem::~DebugSystem(){}

void DebugSystem::update()
{
	if (!mIsActive)
		return;
}

void DebugSystem::draw(GraphicsBuffer* const _backBuffer)
{
	if (!mIsActive)
		return;
}

void DebugSystem::toggle()
{
	toggle(!mIsActive);
}

void DebugSystem::toggle(bool _isOn)
{
	mIsActive = _isOn;
}

void DebugSystem::drawPaths(){}