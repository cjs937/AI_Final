#pragma once
#include "Trackable.h"
#include <fstream>

enum SaveDataType
{
	NONE = -1, 
	GAME
};

//Override to hold data for different saveable objects
struct SaveData
{
public:
	SaveData(SaveDataType _dataType) :dataType(_dataType) {};
	virtual ~SaveData() {};

	virtual std::string getSerializedData() = 0;
	////writes out save data
	//virtual void saveData(std::ofstream &_fout) = 0;
	//loads in save data
	virtual void loadData(std::ifstream &_fin) = 0;

	SaveDataType dataType;
};

class Saveable : public Trackable
{
public:
	Saveable() {};
	virtual ~Saveable(){};

	virtual void save() = 0;
	virtual void load(SaveData* _data) = 0;

	virtual SaveData* getSaveData() { return mSaveData; };
	virtual void setSaveData(SaveData* _saveData) { mSaveData = _saveData; };
protected:
	SaveData* mSaveData;
};