#include "AIUnit.h"
#include "GridSteering.h"
#include "StateHandler.h"
#include "AI_Wander.h"

AIUnit::AIUnit(KUInitData const & _data) : KinematicUnit(_data)
{
	setSteering(new GridSteering(this));

	StateHandler* stateHandler = new StateHandler();
	AI_Wander* newState = new AI_Wander(*this);

	stateHandler->changeState(*newState);

	addComponent(stateHandler);
}

AIUnit::~AIUnit() {}

void AIUnit::move(Vector2D _direction, float _ms)
{
	static_cast<GridSteering*>(getSteering())->move(_direction, _ms);
}