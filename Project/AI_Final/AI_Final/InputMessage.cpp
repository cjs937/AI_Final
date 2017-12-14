#include "InputMessage.h"
#include "InputSystem.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "QuitGameMessage.h"
#include "MovePlayerMessage.h"
#include "DropBombMessage.h"

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
	case ALLEGRO_KEY_W:
	case ALLEGRO_KEY_A:
	case ALLEGRO_KEY_S:
	case ALLEGRO_KEY_D:
	{
		if (mInputType == KEY_HOLD || mInputType == KEY_DOWN)
		{
			Vector2D direction = Vector2D(0, 0);

			if (mKeyCode == ALLEGRO_KEY_W)
				direction = Vector2D(0, -1);
			else if (mKeyCode == ALLEGRO_KEY_A)
				direction = Vector2D(-1, 0);
			else if (mKeyCode == ALLEGRO_KEY_S)
				direction = Vector2D(0, 1);
			else
				direction = Vector2D(1, 0);

			newMessage = new MovePlayerMessage(direction);
		}

		break;
	case ALLEGRO_KEY_SPACE:
	{
		if(mInputType == KEY_DOWN)
			newMessage = new DropBombMessage();

		break;
	}
	}
	default:
		break;
	}

	if(newMessage != NULL)
		gpGameApp->getMessageManager()->addMessage(newMessage, 0);
};