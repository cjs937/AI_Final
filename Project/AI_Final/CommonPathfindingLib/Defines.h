#pragma once

#include <string>

typedef int IDType;
typedef std::string IDDescriptor;

static const IDType INVALID_ID = -1;
static const IDType HIGHEST_ID = 9999;

#define GAME gpGameApp
#define MESSAGE_MANAGER gpGameApp->getMessageManager()
#define GRAPHICS_SYSTEM gpGameApp->getGraphicsSystem()
#define SAVE_SYSTEM gpGameApp->getSaveSystem()
#define BUFFER_MANAGER gpGameApp->getGraphicsBufferManager()
#define SPRITE_MANAGER gpGameApp->getSpriteManager()

#include "../AI_Final/GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "../AI_Final/SaveSystem.h"
#include "../AI_Final/GameMessageManager.h"
