#include "InputMessage.h"
#include "InputSystem.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "QuitGameMessage.h"

void InputMessage::process()
{
	GameMessage* newMessage = NULL;
	//Vector2D playerPosition = gpGameApp->getPlayerUnit()->getPosition();

	switch (mKeyCode)
	{
	case ALLEGRO_KEY_ESCAPE:
	{
		newMessage = new QuitGameMessage();

		break;
	}
	default:
		break;
	}

	if(newMessage != NULL)
		gpGameApp->getMessageManager()->addMessage(newMessage, 0);
};