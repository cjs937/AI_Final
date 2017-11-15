#pragma once
#include "Saveable.h"

const int FPS = 60;
const int FPS_MS = 1000 / FPS;

class Timer;
class SaveSystem;

/*Uncomment for save system unit test*/
//struct GameSaveData : public SaveData
//{
//	GameSaveData() :SaveData(GAME) 
//	{
//		test = 1;
//	};
//
//	~GameSaveData() {};
//
//	std::string getSerializedData() 
//	{
//		std::string output = "";
//
//		output += std::to_string(dataType) + "\n"
//			+ std::to_string(test) + "\n";
//
//		return output;
//	}
//
//	//loads in save data
//	void loadData(std::ifstream &_fin)
//	{
//		std::string junk;
//
//		_fin >> test;
//
//		std::getline(_fin, junk);
//	}
//
//	int test;
//};

class GameApp : public Saveable
{
public:
	GameApp();
	~GameApp();

	void init(int screenWidth, int screenHeight);

	//do stuff before beginning loop
	void startLoop();

	//process the loop
	bool updateLoop();

	//do stuff at end of loop and return whether it should exit or not
	bool endLoop();

	void cleanup();

	float getDeltaTime();

	//Getters
	SaveSystem* getSaveSystem() { return mpSaveSystem; };


private:
	Timer* mpLoopTimer;
	SaveSystem* mpSaveSystem;
	bool mContinueLoop = true;
	float mPrevFrameTime;
	float mLoopStartTime;
};

extern GameApp* gpGameApp;
