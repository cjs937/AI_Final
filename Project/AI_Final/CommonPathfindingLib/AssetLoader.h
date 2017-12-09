#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include "Game.h"
#include "Trackable.h"

#include <fstream>
#include <string>
#include <vector>


const std::string ASSET_REFERENCE = "../Assets.txt";
const std::string LEVEL = "level";
const std::string SPRITE = "sprite";

class AssetLoader : public Trackable
{
public:
	AssetLoader();
	virtual ~AssetLoader();
	void loadAssets();
	virtual void spriteLoad(std::string assetPath, int value);
	virtual void levelLoad(std::string levelName, std::string assetPath);

	//mpLevel vector functions
	void addLevelName(std::string* levelName);
	std::string* getLevelName(int indexPos);
	void clean();
	void deleteUnit(unsigned int indexPos);

	//get the sprites loaded
	inline int getAssetIdMax() { return mAssetId; };

private:
	std::vector<std::string*> mpLevels;
	int mAssetId;
};







#endif // !ASSETLOADER_H

