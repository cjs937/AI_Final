#include "DebugSystem.h"
#include "Defines.h"
#include "GameApp.h"
#include "allegro5\allegro_primitives.h"
#include "PlayerUnit.h"

DebugSystem::DebugSystem()
{
	toggle(true);
}

DebugSystem::~DebugSystem()
{
	for (int i = 0; i < mObjectsThisFrame.size(); ++i)
	{
		delete mObjectsThisFrame[i];

		mObjectsThisFrame[i] = NULL;
	}

	mObjectsThisFrame.clear();
}

void DebugSystem::update()
{
	if (!mIsActive)
		return;
}

void DebugSystem::log(std::string _message, std::ostream & _stream)
{
	_stream << _message << std::endl;
}

void DebugSystem::drawRequest(DebugObject* _object)
{
	mObjectsThisFrame.push_back(_object);
}

void DebugSystem::draw(GraphicsBuffer* _backBuffer)
{
	//saves objects that shouldn't be deleted every frame
	std::vector<DebugObject*> objectsToSave;

	//draws all debug objects
	for (int i = 0; i < mObjectsThisFrame.size(); ++i)
	{
		if (mIsActive)
			mObjectsThisFrame[i]->draw(_backBuffer);

		//If the object shouldn't be deleted add it to the save vector
		if (!mObjectsThisFrame[i]->deleteThisFrame)
		{
			objectsToSave.push_back(mObjectsThisFrame[i]);
			
			continue;
		}

		delete mObjectsThisFrame[i];

		mObjectsThisFrame[i] = NULL;
	}

	//swap values of save vector with objects this frame
	mObjectsThisFrame.swap(objectsToSave);

	objectsToSave.clear();
}

void DebugSystem::toggle()
{
	toggle(!mIsActive);
}

void DebugSystem::toggle(bool _isOn)
{
	mIsActive = _isOn;
}