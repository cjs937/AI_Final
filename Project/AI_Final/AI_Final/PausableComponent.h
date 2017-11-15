#pragma once
#include "Component.h"

class PausableComponent : public Component
{
public:
	PausableComponent():Component(PAUSABLE) {};
	~PausableComponent() {};

	void pause() { mIsPaused = true; };
	void unpause() { mIsPaused = false; };

	bool isPaused() { return mIsPaused; };

private:
	bool mIsPaused;
};