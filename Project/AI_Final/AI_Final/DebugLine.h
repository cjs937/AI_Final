#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "Color.h"
#include "DebugSystem.h"

struct Color;
struct Ray;
class GraphicsBuffer;

struct DebugLine : public DebugObject
{
public:

	DebugLine(Ray* _ray, Color const & _color = Color(GREEN), int _thickness = 1);
	DebugLine(Vector2D const & _start, Vector2D const & _end, Color const & _color = Color(GREEN), int _thickness = 1);

	~DebugLine();

	virtual void draw(GraphicsBuffer* _backBuffer) override;

private:
	Vector2D startPoint;
	Vector2D endPoint;
	Color color;
	int thickness;
};