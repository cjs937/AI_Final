#pragma once
#include "Trackable.h"
#include <vector>

class PausableComponent;

class PauseSystem : public Trackable
{
public:
	PauseSystem();
	~PauseSystem();

	void systemPause();
	void systemUnpause();

	bool addObject(PausableComponent* _object);
	bool removeObject(PausableComponent* _object);

	bool isPaused() { return mIsPaused; };

private:
	bool mIsPaused;
	std::vector<PausableComponent*> mPausableObjects;

};