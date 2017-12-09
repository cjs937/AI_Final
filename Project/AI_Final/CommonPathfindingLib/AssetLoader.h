#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include "Game.h"
#include "Trackable.h"
#include "Sprite.h"

#include <fstream>
#include <string>
#include <vector>


const std::string ASSET_REFERENCE = "../Assets.txt";
const std::string LEVEL = "level";
const std::string SPRITE = "sprite";
const std::string COLLISION = "collision";
const std::string END_OF_LEVEL_ASSETS = "editorEnd";


class AssetLoader : public Trackable
{
public:
	AssetLoader();
	virtual ~AssetLoader();
	void loadAssets();
	virtual void spriteLoad(std::string assetPath, int value, std::string typeOfObject);
	virtual void levelLoad(std::string levelName, std::string assetPath);

	//mpLevel vector functions
	void addLevelName(std::string levelName);
	std::string getLevelName(int indexPos);
	void clean();
	void deleteUnit(unsigned int indexPos);

	//the next two functions working in tandom will be really important
	//you will have to subtract mAssetId from mTotalAssets to get the first non editor sprite
	//keep this in mind when creating units
	//get the sprites loaded
	inline int getAssetIdMax() { return mAssetId; };
	//get the total# of loaded assets
	inline int getTotalLoaded() { return mTotalAssets; };

	//getLevelsLoaded
	inline int getLevelIdMax() { return mLevelId; };

	//loads sprites that cannot be walked into i.e. the number of the sprite
	inline void addCollisionNumber(int* collisionNumber) { mpCollisions.push_back(collisionNumber); };
	inline int* getCollisionNumber(int indexPos) { return mpCollisions.at(indexPos); };
	void cleanCollisions();
	void deleteCollision(unsigned int indexPos);

	Sprite* getAssetName(std::string searchString);
	void setAssetNames(std::string setValue, int spriteValue);

private:
	std::vector<std::string> mpLevels;
	std::vector<int*> mpCollisions;
	std::vector<std::string> mAssetNames;
	int mAssetId, mLevelId, mCountAssets, mTotalAssets;
};

#endif // !ASSETLOADER_H
