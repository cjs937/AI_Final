#include "StateHandler.h"
#include "State.h"

StateHandler::StateHandler():Component(STATE_HANDLER)
{
	mCurrentState = NULL;
}

StateHandler::~StateHandler()
{
	if (mCurrentState != NULL)
		delete mCurrentState;
}

//Updates the current state
void StateHandler::update()
{
	if (mCurrentState == NULL)
		return;

	State* nextState = mCurrentState->update();

	if (nextState != NULL)
	{
		changeState(*nextState);
	}
}

//Changes to state passed in. _exitState decides whether or not the previous state should call its exit function
void StateHandler::changeState(State & _newState, bool _exitCurrentState)
{
	if (mCurrentState != NULL)
	{
		if (_exitCurrentState)
			mCurrentState->onExit();

		delete mCurrentState;
	}

	mCurrentState = &_newState;

	mCurrentState->onEnter();
}