#include "AIUnit.h"
#include "GridSteering.h"

AIUnit::AIUnit(KUInitData const & _data) : KinematicUnit(_data)
{
	setSteering(new GridSteering(this));
}

AIUnit::~AIUnit() {}