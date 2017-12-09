#pragma once
#include "GameMessage.h"
#include "Vector2D.h"

class MovePlayerMessage : public GameMessage
{
public:

	MovePlayerMessage(Vector2D _direction);
	~MovePlayerMessage();

	virtual void process() override;

private:

	Vector2D mDirection;
};