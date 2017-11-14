#pragma once
#include "Trackable.h"
#include <vector>
#include <fstream>

const std::string SAVEFILE_NAME = "Save.txt";

class Saveable;

class SaveSystem : public Trackable
{
public:
	SaveSystem();
	~SaveSystem();

	void saveState(std::string _fileName);
	void loadFromFile(std::string _fileName);
	bool addObject(Saveable* _object);
	bool removeObject(Saveable* _object);

private:
	std::vector<Saveable*> mSaveableObjects;
};
