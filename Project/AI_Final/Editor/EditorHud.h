#pragma once
#include "game.h"
#include "Hud.h"

class Sprite;

const IDType X_POS = 200;
const IDType Y_POS = 200;


class EditorHud : public Hud
{
public:
	EditorHud();
	~EditorHud();

	void update(int type, GraphicsBuffer* _backBuffer);

	void setLevelPath(std::string theString) { mLevelPath = theString; };

private:
	std::string mLevelPath;

};

