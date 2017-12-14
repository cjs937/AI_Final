#include "EditorHud.h"
#include "Sprite.h"

EditorHud::EditorHud()
{
}

EditorHud::~EditorHud()
{
}

void EditorHud::update(int type, GraphicsBuffer* _backBuffer)
{
	Sprite* mSprite = gpGame->getSpriteManager()->getSprite(type);
	mSprite->drawScaled(*_backBuffer, X_POS, Y_POS, 32, 32, 0);
}