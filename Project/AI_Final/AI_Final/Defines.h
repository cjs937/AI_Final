#pragma once
#include <string>
#include "GameApp.h"

typedef int IDType;
typedef std::string IDDescriptor;

const IDType INVALID_ID = -1;
const IDType HIGHEST_ID = 9999;

#define GAME gpGameApp
#define MESSAGE_MANAGER gpGameApp->getMessageManager()
#define GRAPHICS_SYSTEM gpGameApp->getGraphicsSystem()