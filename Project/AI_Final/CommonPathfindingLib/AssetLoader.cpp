#include "AssetLoader.h"
#include "Game.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "GraphicsBuffer.h"

AssetLoader::AssetLoader()
{
	mAssetId = 0;
}

AssetLoader::~AssetLoader()
{
}

void AssetLoader::loadAssets()
{
	std::fstream fin;
	std::string info = "", pathToAsset = "", nameOfAsset = "";
	fin.open(ASSET_REFERENCE);

	if (!fin.good())
		return;

	getline(fin, info);
	while (!fin.eof())
	{
		if (info == SPRITE)
		{
			getline(fin, pathToAsset);
			spriteLoad(pathToAsset, mAssetId);
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

void AssetLoader::spriteLoad(std::string assetPath, int value)
{
	gpGame->getGraphicsBufferManager()->loadBuffer(value, assetPath);
	GraphicsBuffer* newSprite = gpGame->getGraphicsBufferManager()->getBuffer(value);
	if (newSprite != NULL)
		gpGame->getSpriteManager()->createAndManageSprite(value, newSprite, 0, 0, newSprite->getWidth(), newSprite->getHeight());
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