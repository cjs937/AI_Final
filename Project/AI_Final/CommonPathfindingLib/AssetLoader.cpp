#include "AssetLoader.h"
#include "Game.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "GraphicsBuffer.h"

AssetLoader::AssetLoader()
	//: mpLevels(NULL)
	//, mpCollisions(NULL)
{
	mAssetId = 0;
}

AssetLoader::~AssetLoader()
{
	clean();
	cleanCollisions();
}

void AssetLoader::loadAssets()
{
	std::fstream fin;
	std::string info = "", pathToAsset = "", nameOfAsset = "", assetType = "";
	fin.open(ASSET_REFERENCE);

	if (!fin.good())
		return;

	getline(fin, info);
	while (!fin.eof())
	{
		if (info == SPRITE)
		{
			getline(fin, pathToAsset);
			getline(fin, assetType);
			spriteLoad(pathToAsset, mAssetId, assetType);
			mAssetId += 1;
		}
		else if (info == LEVEL)
		{
			getline(fin, pathToAsset);
			getline(fin, nameOfAsset);
			levelLoad(nameOfAsset, pathToAsset);
		}
		getline(fin, info);
	}
	fin.close();
}

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

void AssetLoader::levelLoad(std::string levelName, std::string assetPath)
{

}

void AssetLoader::addLevelName(std::string* levelName)
{
	mpLevels.push_back(levelName);
}

std::string* AssetLoader::getLevelName(int indexPos)
{
	return mpLevels.at(indexPos);
}

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
	delete mpLevels.at(indexPos);
}

void AssetLoader::cleanCollisions()
{
	for (unsigned int i = 0; i < mpCollisions.size(); ++i)
		deleteUnit(i);
	mpCollisions.clear();
}

void AssetLoader::deleteCollision(unsigned int indexPos)
{
	if (indexPos < 0 || indexPos >= mpCollisions.size())
		return;
	delete mpCollisions.at(indexPos);
}