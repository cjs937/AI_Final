#include "DebugSystem.h"
#include "Defines.h"
#include "GameApp.h"
#include "allegro5\allegro_primitives.h"
#include "PlayerUnit.h"

DebugSystem::DebugSystem()
{
	toggle(true);
}

DebugSystem::~DebugSystem(){}

void DebugSystem::update()
{
	if (!mIsActive)
		return;
}

void DebugSystem::draw(GraphicsBuffer* const _backBuffer)
{
	if (!mIsActive)
		return;

	PlayerUnit* player = UNIT_MANAGER->getPlayerUnit();

	if (player == NULL)
		return;

	Vector2D start = player->getCenterPosition();

	Vector2D end = player->getSteering()->getLinear();

	end.normalize();

	end *= UNIT_MANAGER->getUnitData()->raycastDistance;

	end += start;

	if (end == Vector2D(0, 0))
		return;

	al_draw_line(start.getX(), start.getY(), end.getX(), end.getY(), al_map_rgb(255, 0, 0), 1);
}

void DebugSystem::toggle()
{
	toggle(!mIsActive);
}

void DebugSystem::toggle(bool _isOn)
{
	mIsActive = _isOn;
}

void DebugSystem::drawPaths(){}