#include "AssetLoader.h"
#include "Game.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "GraphicsBuffer.h"
#include <sstream>

AssetLoader::AssetLoader()
{
	mAssetId = 0;
	mLevelId = 0;
	mTotalAssets = 0;
	mCountAssets = 1;
}

AssetLoader::~AssetLoader()
{
	//clean();
	//cleanCollisions();
}
//this is the big boy here
void AssetLoader::loadAssets()
{
	std::fstream fin;
	std::string info = "", pathToAsset = "", nameOfAsset = "", assetType = "";
	fin.open(ASSET_REFERENCE); // ASSET_REFERENCE is a .txt that holds all the needed info

	if (!fin.good())
		return;

	getline(fin, info); // get first line of the file for error checking etc.
	while (!fin.eof())
	{
		//the file will be broken up into two parts 
		//this is mainly for sprites so the editor knows 
		//which sprites it is allowed to use refer to the 
		//Readme in the same folder location
		if (info == END_OF_LEVEL_ASSETS)
			mCountAssets = 0;
		else if (info == SPRITE) // will execute this code if the type of thing being read is a sprite
		{
			getline(fin, pathToAsset);
			getline(fin, assetType);
			getline(fin, nameOfAsset);
			spriteLoad(pathToAsset, mTotalAssets, assetType);
			setAssetNames(nameOfAsset, mTotalAssets);
			mAssetId += mCountAssets; // will be added to until the END_OF_LEVEL_ASSETS is found
			mTotalAssets++; // tracks all sprites loaded
		}
		else if (info == LEVEL) // this will load the level, up to this point there is no use for the name of the level
		{
			getline(fin, pathToAsset);
			getline(fin, nameOfAsset);
			levelLoad(nameOfAsset, pathToAsset);
			mLevelId++;
		}
		getline(fin, info);
	}
	fin.close();
}

//loads the sprite into the graphics buffer, as well as adds to a list of all objects that should be collided with
void AssetLoader::spriteLoad(std::string assetPath, int value, std::string typeOfObject)
{
	//send to game a list of objects that can be played with
	gpGame->getGraphicsBufferManager()->loadBuffer(value, assetPath);
	GraphicsBuffer* newSprite = gpGame->getGraphicsBufferManager()->getBuffer(value);
	if (newSprite != NULL)
		gpGame->getSpriteManager()->createAndManageSprite(value, newSprite, 0, 0, newSprite->getWidth(), newSprite->getHeight());
	if (typeOfObject == COLLISION)
		addCollisionNumber(&value);
}

// just calls addLevelName to store the level
void AssetLoader::levelLoad(std::string levelName, std::string assetPath)
{
	addLevelName(assetPath);
}

//stores the level into mpLevels
void AssetLoader::addLevelName(std::string levelName)
{
	mpLevels.push_back(levelName);
}

//Gets the name of the level
std::string AssetLoader::getLevelName(int indexPos)
{
	return mpLevels.at(indexPos);
}

//the clean functions arnt really needed
void AssetLoader::clean()
{
	for (unsigned int i = 0; i < mpLevels.size(); ++i)
		deleteUnit(i);
	mpLevels.clear();
}

void AssetLoader::deleteUnit(unsigned int indexPos)
{
	if (indexPos < 0 || indexPos >= mpLevels.size())
		return;
	//delete mpLevels.at(indexPos);
}

void AssetLoader::cleanCollisions()
{
	for (unsigned int i = 0; i < mpCollisions.size(); ++i)
		deleteCollision(i);
	mpCollisions.clear();
}

void AssetLoader::deleteCollision(unsigned int indexPos)
{
	if (indexPos < 0 || indexPos >= mpCollisions.size())
		return;
	delete mpCollisions.at(indexPos);
}

Sprite* AssetLoader::getAssetName(std::string searchString)
{
	for (unsigned int i = 0; i < mAssetNames.size(); i++)
	{
		if (mAssetNames.at(i) == searchString)
		{
			i++;
			return gpGame->getSpriteManager()->getSprite(atoi(mAssetNames.at(i).c_str()));
		}
	}
	return NULL;
}

void AssetLoader::setAssetNames(std::string setValue, int spriteVal)
{
	std::stringstream change;
	std::string newName;
	change << spriteVal;
	change >> newName;
	mAssetNames.push_back(setValue);
	mAssetNames.push_back(newName);
}