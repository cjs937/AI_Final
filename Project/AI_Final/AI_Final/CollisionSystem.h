#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class KinematicUnit;
class Steering;
struct Ray;

const float UNIT_RAYCAST_DISTANCE = 70.0f;
const float WALL_AVOID = 50.0f;

struct RayCollision : public Trackable
{
	RayCollision(bool _hit, Vector2D _position) : hit(_hit), position(_position)
	{}
	~RayCollision()
	{}

	bool hit;
	Vector2D position;
};

class CollisionSystem : public Trackable
{
public:
	static bool checkTerrainCollision(Vector2D _start, Vector2D _direction, float _castDistance);
	static bool checkTerrainCollision(KinematicUnit* _unit, Steering* _steering);
	static bool checkTerrainCollision(Ray* _ray);
private:

	static bool rayCast(Ray* _ray);
	//static RayCollision* rayIntersectsSegment(Ray* _ray, Vector2D _pointA, Vector2D _pointB);
	//static RayCollision* checkWallIntersection(KinematicUnit* _unit, TerrainUnit* _wall);
};