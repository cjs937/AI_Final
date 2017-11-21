#pragma once
#include <map>
#include <vector>
#include <stack>
#include "Defines.h"

enum UnitType
{
	NONE = -1,
	PLAYER,
	AI,	
	WALL,
	CIRCLE,
	NUM_TYPES
};

const float DEFAULT_MAX_VEL = 100.0f;
const float DEFAULT_MAX_ROTATION = 100.0f;//0.5f;

enum ComponentType;
class Component;
class TerrainUnit;
class KinematicUnit;

class UnitManager : public Trackable
{
private:
	//map of unit maps
	std::map<UnitType, std::map<int, KinematicUnit*>*> mMapList;
	std::map<UnitType, IDType> mBufferIDs;
//	std::vector<TerrainUnit*> mTerrain;
	std::stack<int> mAvailableIDs;

	void initBuffersAndSprites();
	Sprite* getUnitSprite(UnitType _unitType);
	IDType getBufferID(UnitType _unitType);

	float mUnitMaxVelocity;
	float mUnitMaxRotationVelocity;

public:
	UnitManager();
	~UnitManager();

	std::map<UnitType, std::map<int, KinematicUnit*>*>* getMapList() { return &mMapList; }

	void update(float _dt);
	void draw(GraphicsBuffer* _buffer);


	std::map<int, KinematicUnit*>* getUnitMap(UnitType _type);
	//std::vector<TerrainUnit*> getTerrain() { return mTerrain; };
	KinematicUnit* getUnit(int _ID, UnitType _type);


	//void generateBorderWall(int _width, int _height);
	KinematicUnit* addUnit(UnitType _type, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	bool removeUnit(int _ID);
	void removeRandomUnit();
	Component* addComponent(ComponentType _type, KinematicUnit* _unit);
	Component* addComponent(Component* component, KinematicUnit* _unit);

	//void  spawnCircle(Vector2D _position);
	//bool tagExists(int _ID);
};