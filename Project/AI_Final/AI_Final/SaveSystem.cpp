#include "SaveSystem.h"
#include "SaveableObjects.h"
#include  <fstream>
#include <string>

SaveSystem::SaveSystem()
{}

SaveSystem::~SaveSystem()
{}

void SaveSystem::saveState(std::string _fileName)
{
	std::ofstream fout;
	fout.open(_fileName);

	for (int i = 0; i < mSaveableObjects.size(); ++i)
	{
		Saveable* currObject = mSaveableObjects[i];
		
		currObject->save(fout);
	}
}

void SaveSystem::loadFromFile(std::string _fileName)
{
	std::ifstream fin;
	//std::string currentLine;
	int currentType;

	fin.open(_fileName);

	if (fin.fail())
	{
		std::cout << "Error opening " + _fileName + "\n";

		return;
	}

	try
	{
		while (fin.peek() != EOF)//fin.eof())
		{
			std::string junk;

			//reads in SaveDataType
			fin >> currentType;
			//cleans stream
			std::getline(fin, junk);

			//reads first line to find what type of data to parse
			if (currentType == GAME)
			{
				//create game SaveData object
				//call loadData on object
				//send gamemessage for loading that data type

				/*Uncomment for save system unit test*/
				//GameSaveData* gameData = new GameSaveData();
				//gameData->loadData(fin);
				//gpGameApp->load(gameData);
			}
			else //if the parser reads in a line that isn't recognized here it is out of sync
			{		
				throw;
			}
		}
	}
	catch(...)
	{
		std::cout << "Error parsing game data, load must stop\n";

		return;
	}
}

bool SaveSystem::addObject(Saveable* _object)
{
	//checks if object already exists first
	for (auto currObject = mSaveableObjects.begin(); currObject != mSaveableObjects.end(); ++currObject)
	{
		if (*currObject == _object)
		{
			return false;
		}
	}

	mSaveableObjects.push_back(_object);

	return true;
}

bool SaveSystem::removeObject(Saveable* _object)
{
	for (auto currObject = mSaveableObjects.begin(); currObject != mSaveableObjects.end(); ++currObject)
	{
		if (*currObject == _object)
		{
			mSaveableObjects.erase(currObject);
			
			return true;
		}
	}

	return false;
}