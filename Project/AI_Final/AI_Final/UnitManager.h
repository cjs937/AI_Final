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
	BOMB,
	EXPLOSION,
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
class SpawnSystem;

struct SharedUnitData : public SaveData
{
public:

	SharedUnitData(float _playerSpeed, float _aiSpeed, float _raycastDistance, float _playerBombDropDelay, float _bombExplosionDelay, float _explosionUptime);
	~SharedUnitData();

	virtual std::string getSerializedData() override;

	virtual void loadData(std::ifstream &_fin) override;

	float playerSpeed;
	float aiSpeed;
	float raycastDistance;
	float bombExplosionDelay;
	float playerBombDropDelay;
	float explosionUptime;
};

class UnitManager : public Trackable
{
private:

	//map of unit maps
	std::map<UnitType, std::map<IDType, KinematicUnit*>*> mMapList;
	std::stack<int> mAvailableIDs;

	SpawnSystem* mpSpawnSystem;

	SaveableComponent* mSaveComponent;

	Sprite* getUnitSprite(UnitType _unitType);

	IDType mPlayerID;
public:
	UnitManager(SharedUnitData* _saveData);
	~UnitManager();

	void init();
	void update(float _dt);
	void draw(GraphicsBuffer* _buffer);

	KinematicUnit* addUnit(UnitType _type, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f);
	bool removeUnit(int _ID);
	void removeRandomUnit();

	Component* addComponent(ComponentType _type, KinematicUnit* _unit);
	Component* addComponent(Component* component, KinematicUnit* _unit);

	//Accessors
	std::map<UnitType, std::map<int, KinematicUnit*>*> getMapList() { return mMapList; }
	std::map<int, KinematicUnit*>* getUnitMap(UnitType _type);
	KinematicUnit* getUnit(int _ID, UnitType _type);
	PlayerUnit* getPlayerUnit();
	SharedUnitData* getUnitData();
	SpawnSystem* getSpawnSystem() { return mpSpawnSystem; };
	int getPlayerID() { return mPlayerID; };


};