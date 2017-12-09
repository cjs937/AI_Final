#pragma once
#include <map>
#include <vector>
#include <stack>
#include "Defines.h"
#include "SaveableComponent.h"

enum UnitType
{
	//NONE = -1,
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
class SaveableComponent;
class PlayerUnit;
class Sprite;

struct SharedUnitData : public SaveData
{
public:

	SharedUnitData(float _playerSpeed, float _aiSpeed);
	~SharedUnitData();

	virtual std::string getSerializedData() override;

	virtual void loadData(std::ifstream &_fin) override;

	float playerSpeed;
	float aiSpeed;
};

class UnitManager : public Trackable
{
private:
	//map of unit maps
	std::map<UnitType, std::map<IDType, KinematicUnit*>*> mMapList;
	std::map<UnitType, IDType> mBufferIDs;
//	std::vector<TerrainUnit*> mTerrain;
	std::stack<int> mAvailableIDs;

	SaveableComponent* mSaveComponent;

	void initBuffersAndSprites();
	Sprite* getUnitSprite(UnitType _unitType);
	IDType getBufferID(UnitType _unitType);

	float mUnitMaxVelocity;
	float mUnitMaxRotationVelocity;

	IDType mPlayerID;
public:
	UnitManager(SharedUnitData* _saveData);
	~UnitManager();

	std::map<UnitType, std::map<int, KinematicUnit*>*>* getMapList() { return &mMapList; }

	void update(float _dt);
	void draw(GraphicsBuffer* _buffer);

	int getPlayerID() { return mPlayerID; };
	PlayerUnit* getPlayerUnit();

	std::map<int, KinematicUnit*>* getUnitMap(UnitType _type);
	//std::vector<TerrainUnit*> getTerrain() { return mTerrain; };
	KinematicUnit* getUnit(int _ID, UnitType _type);

	KinematicUnit* addUnit(UnitType _type, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	bool removeUnit(int _ID);
	void removeRandomUnit();
	Component* addComponent(ComponentType _type, KinematicUnit* _unit);
	Component* addComponent(Component* component, KinematicUnit* _unit);

	SharedUnitData* getUnitData();

};