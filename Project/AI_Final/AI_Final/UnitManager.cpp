#include "UnitManager.h"
#include "GameApp.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "GraphicsBuffer.h"
#include "Component.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "AIUnit.h"
#include "PlayerUnit.h"
#include "AssetLoader.h"
#include "SpawnSystem.h"
#include "CollisionSystem.h"
#include "Bomb.h"
#include "Explosion.h"

typedef std::pair <UnitType, std::map<int, KinematicUnit*>*> mapListPair;
typedef std::pair <int, KinematicUnit*> mapPair;
typedef pair<UnitType, IDType> IDPair;

/*SharedUnitData functions */

SharedUnitData::SharedUnitData(float _playerSpeed, float _aiSpeed, float _raycastDistance, float _playerBombDropDelay, float _bombExplosionDelay,  float _explosionUptime): SaveData(UNIT_VALUES),
playerSpeed(_playerSpeed), aiSpeed(_aiSpeed), raycastDistance(_raycastDistance), playerBombDropDelay(_playerBombDropDelay), explosionUptime(_explosionUptime), bombExplosionDelay(_bombExplosionDelay)
{}

SharedUnitData::~SharedUnitData()
{}

std::string SharedUnitData::getSerializedData()
{
	return "";
}

void SharedUnitData::loadData(std::ifstream &_fin)
{}

//////////////////////////////////////////////

/*Unit Manager Functions*/
UnitManager::UnitManager(SharedUnitData* _saveData) : mPlayerID(INVALID_ID)
{
	mSaveComponent = new SaveableComponent(_saveData);
}

SharedUnitData* UnitManager::getUnitData()
{
	return static_cast<SharedUnitData*>(mSaveComponent->getSaveData());
}

void UnitManager::init()
{
	//first unit id will be 0
	mAvailableIDs.push(0);

	mpSpawnSystem = new SpawnSystem();

	mpSpawnSystem->initSpawners(gpGameApp->getGrid());
}


UnitManager::~UnitManager()
{
	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
			delete j->second;

		i->second->clear();
	}

	mMapList.clear();

	if (mpSpawnSystem != NULL)
	{
		delete mpSpawnSystem;

		mpSpawnSystem = NULL;
	}

	if (mSaveComponent != NULL)
	{
		delete mSaveComponent;

		mSaveComponent = NULL;
	}
}

std::map<int, KinematicUnit*>* UnitManager::getUnitMap(UnitType _type)
{
	try
	{
		return mMapList[_type];
	}
	catch (std::out_of_range)
	{
		return NULL;
	}
}


KinematicUnit* UnitManager::getUnit(int _ID, UnitType _type)
{
	if (_type == NONE)
	{
		for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
		{
			for (auto j = i->second->begin(); j != i->second->end(); ++j)
			{
				if(j->second->getID() == _ID)
					return j->second;
			}
		}
	}
	else
	{
		for (auto i = mMapList[_type]->begin(); i != mMapList[_type]->end(); ++i)
		{
			if (i->second->getID() == _ID)
				return i->second;
		}
	}

	return NULL;
}


void UnitManager::update(float _dt)
{
	CollisionSystem::checkAllUnitCollisions();

	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			j->second->update(_dt);
		}
	}

	mpSpawnSystem->update(_dt);
}

void UnitManager::draw(GraphicsBuffer* _buffer)
{
	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			j->second->draw(_buffer);
		}
	}
}


KinematicUnit* UnitManager::addUnit(UnitType _type, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, float maxVelocity, float maxAcceleration)
{
	Sprite* unitSprite = getUnitSprite(_type);

	if (unitSprite == NULL)
	{
		return NULL;
	}

	if (mMapList.find(_type) == mMapList.end())
	{
		mMapList.insert(mapListPair(_type, new std::map<int, KinematicUnit*>));
	}
	else if (_type == PLAYER) // if player map exists return since there should only be one
		return NULL;

	int newID = mAvailableIDs.top();

	mAvailableIDs.pop();

	if (_type == PLAYER)
		mPlayerID = newID;

	if (mAvailableIDs.empty())
		mAvailableIDs.push(newID + 1);

	KinematicUnit* newUnit;

	KUInitData unitData(_type, newID, unitSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);

	switch (_type)
	{
	case(PLAYER):
		newUnit = new PlayerUnit(unitData);
		break;
	case(AI):
		newUnit = new AIUnit(unitData);
		break;
	case(BOMB):
		newUnit = new Bomb(unitData);
		break;
	case(EXPLOSION):
		newUnit = new Explosion(unitData);
		break;
	default:
		newUnit = new KinematicUnit(unitData);
		break;
	}

	mMapList[_type]->insert(mapPair(newID, newUnit));

	return newUnit;
}

Sprite* UnitManager::getUnitSprite(UnitType _unitType)
{
	IDType spriteID;

	if (_unitType == PLAYER)
	{
		spriteID = gpGameApp->getAssetLoader()->getAssetIndex(PLAYER_ID);
	}
	else if (_unitType == BOMB)
	{
		spriteID = gpGameApp->getAssetLoader()->getAssetIndex(BOMB_ID);
	}
	else if(_unitType == EXPLOSION)
	{
		spriteID = gpGameApp->getAssetLoader()->getAssetIndex(EXPLOSION_ID);
	}
	else
	{
		spriteID = gpGameApp->getAssetLoader()->getAssetIndex(AI_ID);
	}

	return gpGameApp->getSpriteManager()->getSprite(spriteID);
}


bool UnitManager::removeUnit(int _ID)
{
	std::map<int, KinematicUnit*>::iterator mapIterator;

	for (auto unitMap = mMapList.begin(); unitMap != mMapList.end(); ++unitMap)
	{
		mapIterator = unitMap->second->find(_ID);

		if(mapIterator == unitMap->second->end())
			continue;
		else
		{
			//push unit's id into available id list so it can be used again
			mAvailableIDs.push(mapIterator->second->getID());

			delete mapIterator->second;
			mapIterator->second = NULL;

			unitMap->second->erase(mapIterator);

			//erases map if it is empty
			if (unitMap->second->size() == 0)
				mMapList.erase(unitMap);

			return true;
		}
	}

	return false;
}

void UnitManager::removeRandomUnit()
{
	if (mMapList.size() == 1)
		return;

	UnitType randMap;
	int randNum;

	do
	{
		srand(GAME->getCurrentTime() + 1);

		//generate random number between 1 and the number of unit types. 0 is ommited so player unit is not deleted
		randNum = (rand() % NUM_TYPES) + 1;

		randMap = static_cast<UnitType>(randNum);
	} while (mMapList.find(randMap) == mMapList.end());

	randNum = rand() % mMapList.at(randMap)->size();

	int i = 0;
	KinematicUnit* toRemove = NULL;

	for (auto mapIterator = mMapList.at(randMap)->begin(); mapIterator != mMapList.at(randMap)->end(); ++mapIterator)
	{
		if (i == randNum)
		{
			toRemove = mapIterator->second;

			break;
		}

		++i;
	}

	if (toRemove == NULL)
	{
		std::cout << "Error removing random unit\n";

		return;
	}

	removeUnit(toRemove->getID());
}

Component* UnitManager::addComponent(ComponentType _type, KinematicUnit* _unit)
{
	Component* newComponent = NULL;


	//Create new component based on _type
	switch (_type)
	{
	default:
		break;
	}

	return addComponent(newComponent, _unit);
}

Component* UnitManager::addComponent(Component* _component, KinematicUnit* _unit)
{
	_unit->addComponent(_component);

	return _component;
}

PlayerUnit* UnitManager::getPlayerUnit()
{
	if (mPlayerID == INVALID_ID)
		return NULL;

	return static_cast<PlayerUnit*>(getUnit(mPlayerID, PLAYER));
}
