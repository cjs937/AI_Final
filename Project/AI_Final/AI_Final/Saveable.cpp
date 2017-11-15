#include "Saveable.h"

Saveable::Saveable(SaveData* _saveData):mSaveData(NULL)
{
	setSaveData(_saveData);
}

Saveable::~Saveable() 
{}

void Saveable::save(std::ofstream &_fout)
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

void Saveable::load(SaveData* _data)
{
	setSaveData(_data);
}

void Saveable::load(std::ifstream &_fin)
{
	mSaveData->loadData(_fin);
};

void Saveable::setSaveData(SaveData* _saveData) 
{ 
	if (mSaveData != NULL)
	{
		delete mSaveData;
	}

	mSaveData = _saveData;
};