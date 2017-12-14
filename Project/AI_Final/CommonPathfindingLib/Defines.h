#pragma once

#include <string>

typedef int IDType;
typedef std::string IDDescriptor;

static const IDType INVALID_ID = -1;
static const IDType HIGHEST_ID = 9999;

static const IDDescriptor ERROR_STRING = "error";
static const IDDescriptor WALL_STRING = "wall";


const IDType WIDTH = 1024;
const IDType HEIGHT = 768;

const int GRID_SQUARE_SIZE = 32;


#define GAME gpGameApp
#define MESSAGE_MANAGER gpGameApp->getMessageManager()
#define GRAPHICS_SYSTEM gpGameApp->getGraphicsSystem()
#define SAVE_SYSTEM gpGameApp->getSaveSystem()
#define BUFFER_MANAGER gpGameApp->getGraphicsBufferManager()
#define SPRITE_MANAGER gpGameApp->getSpriteManager()
#define UNIT_MANAGER gpGameApp->getUnitManager()
#define DEBUG gpGameApp->getDebugSystem()

//#include "../AI_Final/GameApp.h"

#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "../AI_Final/SaveSystem.h"
#include "../AI_Final/GameMessageManager.h"
#include "../AI_Final/UnitManager.h"
#include "../AI_Final/DebugSystem.h"
