#pragma once
#include "Component.h"
#include <fstream>
#include <string>

enum SaveDataType
{
	NONE = -1, 
	GAME_APP,
	UNIT_VALUES
};

//Override to hold data for different saveable objects
struct SaveData
{
public:
	SaveData(SaveDataType _dataType) :dataType(_dataType) {};
	virtual ~SaveData() {};

	//returns string with data that should be saved to file
	//only one piece of info per line
	//all lines end with a \n
	virtual std::string getSerializedData() = 0;

	//loads in save data based on format in getSeralizedData()
	virtual void loadData(std::ifstream &_fin) = 0;

	SaveDataType dataType;
};

class SaveableComponent : public Component
{
public:
	SaveableComponent(SaveData* _saveData = NULL);
	virtual ~SaveableComponent() override;

	virtual void save(std::ofstream &_fout);
	//virtual void save(std::string _fileName);
	virtual void load(SaveData* _data);
	virtual void load(std::ifstream &_fin);

	virtual SaveData* getSaveData() { return mSaveData; };
	virtual void setSaveData(SaveData* _saveData);

private:
	SaveData* mSaveData;
};