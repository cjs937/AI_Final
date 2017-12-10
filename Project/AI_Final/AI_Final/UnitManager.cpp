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

typedef std::pair <UnitType, std::map<int, KinematicUnit*>*> mapListPair;
typedef std::pair <int, KinematicUnit*> mapPair;
typedef pair<UnitType, IDType> IDPair;


SharedUnitData::SharedUnitData(float _playerSpeed, float _aiSpeed, float _raycastDistance): SaveData(UNIT_VALUES),
playerSpeed(_playerSpeed), aiSpeed(_aiSpeed), raycastDistance(_raycastDistance)
{}

SharedUnitData::~SharedUnitData()
{}

std::string SharedUnitData::getSerializedData()
{
	return "";
}

void SharedUnitData::loadData(std::ifstream &_fin)
{}

UnitManager::UnitManager(SharedUnitData* _saveData) : mPlayerID(INVALID_ID)
{
	mSaveComponent = new SaveableComponent(_saveData);

	mUnitMaxVelocity = DEFAULT_MAX_VEL;
	mUnitMaxRotationVelocity = DEFAULT_MAX_ROTATION;

	initBuffersAndSprites();

	//first unit id will be 0
	mAvailableIDs.push(0);
}

SharedUnitData* UnitManager::getUnitData()
{
	return static_cast<SharedUnitData*>(mSaveComponent->getSaveData());
}


void UnitManager::initBuffersAndSprites()
{
	mBufferIDs.insert(IDPair(AI, gpGameApp->getGraphicsBufferManager()->loadBuffer("enemy-arrow.bmp")));

	GraphicsBuffer* pAIBuffer = gpGameApp->getGraphicsBufferManager()->getBuffer(getBufferID(AI));
	if (pAIBuffer != NULL)
	{
		gpGameApp->getSpriteManager()->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight());
	}
}

IDType UnitManager::getBufferID(UnitType _unitType)
{
	if (mBufferIDs.find(_unitType) == mBufferIDs.end())
		return INVALID_ID;

	return mBufferIDs[_unitType];
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
	for (auto i = mMapList.begin(); i != mMapList.end(); ++i)
	{
		for (auto j = i->second->begin(); j != i->second->end(); ++j)
		{
			j->second->update(_dt);
		}
	}
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
	Sprite* unitSprite = getUnitSprite(AI);

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

	KUInitData unitData(newID, unitSprite, position, orientation, velocity, rotationVel, maxVelocity, maxAcceleration);

	switch (_type)
	{
	case(PLAYER):
		newUnit = new PlayerUnit(getUnitData()->playerSpeed, unitData);
		break;
	case(AI):
		newUnit = new AIUnit(unitData);
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
		spriteID = PLAYER_ICON_SPRITE_ID;
	}
	else if (_unitType == WALL)
	{
		spriteID = WALL_SPRITE_ID;
	}
	else if (_unitType == CIRCLE)
	{
		spriteID = CIRCLE_SPRITE_ID;
	}
	else
	{
		spriteID = AI_ICON_SPRITE_ID;
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
