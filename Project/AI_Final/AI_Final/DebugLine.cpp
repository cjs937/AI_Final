#include "DebugLine.h"
#include "Ray.h"
#include "allegro5\allegro_primitives.h"

DebugLine::DebugLine(Ray* _ray, Color const & _color, int _thickness)
	:color(_color), thickness(_thickness)
{
	startPoint = _ray->getSourcePoint();

	endPoint = _ray->getPointAlongRay(1.0f);
}

DebugLine::DebugLine(Vector2D const & _start, Vector2D const & _end, Color const & _color, int _thickness)
	:startPoint(_start), endPoint(_end), color(_color), thickness(_thickness)
{}

DebugLine::~DebugLine()
{}

void DebugLine::draw(GraphicsBuffer* _backBuffer)
{
	al_draw_line(startPoint.getX(), startPoint.getY(), endPoint.getX(), endPoint.getY(), color.color, thickness);
}