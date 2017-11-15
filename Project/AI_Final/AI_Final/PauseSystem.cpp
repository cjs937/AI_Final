#include "PauseSystem.h"
#include "PausableComponent.h"

PauseSystem::PauseSystem() {};

PauseSystem::~PauseSystem() {};

void PauseSystem::systemPause() 
{
	//pause all objects
	for (int i = 0; i < mPausableObjects.size(); ++i)
	{
		mPausableObjects[i]->pause();
	}

	mIsPaused = true;
}

void PauseSystem::systemUnpause()
{
	//unpause all objects
	for (int i = 0; i < mPausableObjects.size(); ++i)
	{
		mPausableObjects[i]->unpause();
	}

	mIsPaused = false;
}


bool PauseSystem::addObject(PausableComponent* _object)
{
	//checks if object already exists first
	for (auto currObject = mPausableObjects.begin(); currObject != mPausableObjects.end(); ++currObject)
	{
		if (*currObject == _object)
		{
			return false;
		}
	}

	mPausableObjects.push_back(_object);

	return true;
}

bool PauseSystem::removeObject(PausableComponent* _object)
{
	//searches vector for object
	for (auto currObject = mPausableObjects.begin(); currObject != mPausableObjects.end(); ++currObject)
	{
		if (*currObject == _object)
		{
			mPausableObjects.erase(currObject);

			return true;
		}
	}

	//if object wasn't found
	return false;
}