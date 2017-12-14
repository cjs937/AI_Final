#pragma once

#include <list>
#include "Trackable.h"

class GameMessages;

class GameMessageManager: public Trackable
{
public:
	GameMessageManager();
	~GameMessageManager();

	void addMessage( GameMessages* pMessage, int delay );//note - message manager will now "own" the message and will delete it at its pleasure
	void processMessagesForThisframe();

private:

	std::list<GameMessages*> mMessages;
};

