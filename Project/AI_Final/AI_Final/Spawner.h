#pragma once
#include "Trackable.h"
#include "Vector2D.h"

enum SpawnerType
{
	PLAYER_SPAWN,
	ENEMY_SPAWN,
	POWERUP_SPAWN,
	WALL_SPAWN
};

class Timer;

class Spawner : public Trackable
{
public:
	Spawner(SpawnerType _type, Vector2D _position, bool _spawnOnStart = true);
	virtual ~Spawner();

	SpawnerType getType() { return mType; };
	Vector2D const getPosition() { return mPosition; };
	bool spawnOnStart() { return mSpawnOnStart; };
	virtual void spawnDelayedObject(float _delay);

	//Should be overridden by children
	virtual void update();
	virtual void spawnObject() = 0;
	//Make sure object spawner is spawning can be spawned at this time
	virtual bool canSpawn() = 0;
	
private:
	Timer* mpTimer;
	SpawnerType mType;
	Vector2D mPosition;

	bool mSpawnOnStart;
	bool mDelaying;
	float mCurrentSpawnDelay;
};