#include "SaveableComponent.h"
#include "Defines.h"

SaveableComponent::SaveableComponent(SaveData* _saveData):Component(SAVEABLE), mSaveData(NULL)
{
	setSaveData(_saveData);

	if (GAME != NULL)
		if (SAVE_SYSTEM != NULL)
			SAVE_SYSTEM->addObject(this);
}

SaveableComponent::~SaveableComponent() 
{
	if (mSaveData != NULL)
		delete mSaveData;
}

void SaveableComponent::save(std::ofstream &_fout)
{
	_fout << mSaveData->getSerializedData();
}

//void Saveable::save(std::string _fileName)
//{
//	std::ofstream fout;
//
//	fout.open(_fileName, std::ofstream::app);
//
//	if (fout.fail())
//	{
//		std::cout << "Could not open " << _fileName << std::endl;
//
//		return;
//	}
//
//	fout << mSaveData->getSerializedData();
//
//	fout.close();
//}

void SaveableComponent::load(SaveData* _data)
{
	setSaveData(_data);
}

void SaveableComponent::load(std::ifstream &_fin)
{
	mSaveData->loadData(_fin);
};

void SaveableComponent::setSaveData(SaveData* _saveData) 
{ 
	if (mSaveData != NULL)
	{
		delete mSaveData;
	}

	mSaveData = _saveData;
};