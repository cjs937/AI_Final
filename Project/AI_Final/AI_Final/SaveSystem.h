#pragma once
#include "Trackable.h"
#include <vector>
#include <fstream>

const std::string SAVEFILE_NAME = "Save.txt";

class SaveableComponent;

class SaveSystem : public Trackable
{
public:
	SaveSystem();
	~SaveSystem();

	void saveState(std::string _fileName);
	void loadFromFile(std::string _fileName);
	bool addObject(SaveableComponent* _object);
	bool removeObject(SaveableComponent* _object);

private:
	std::vector<SaveableComponent*> mSaveableObjects;
};
