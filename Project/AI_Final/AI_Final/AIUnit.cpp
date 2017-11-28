#include "AIUnit.h"

AIUnit::AIUnit(KUInitData const & _data) : KinematicUnit(_data)
{
	std::cout << "creating AI unit\n";
}

AIUnit::~AIUnit() {}