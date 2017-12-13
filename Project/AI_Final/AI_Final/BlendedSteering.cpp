#include "BlendedSteering.h"
#include "GameApp.h"
#include "UnitManager.h"

BlendedSteering::BlendedSteering(KinematicUnit* _unit)
{
	//BlendedSteeringBehavior* collisionBehavior = new BlendedSteeringBehavior(new CollisionSteering(_unit), 3.0f);

	//mBehaviors.push_back(collisionBehavior);
}

BlendedSteering::~BlendedSteering()
{
	for (unsigned int i = 0; i < mBehaviors.size(); ++i)
	{
		delete mBehaviors[i];

		mBehaviors[i] = NULL;
	}

	mBehaviors.clear();
}

Steering* BlendedSteering::getSteering()
{
	Steering* steering = this;
	mLinear = Vector2D();
	mAngular = 0;

	for (unsigned int i = 0; i < mBehaviors.size(); ++i)
	{
		Steering* currentSteering = mBehaviors[i]->steeringBehavior->getSteering();
		float weight = mBehaviors[i]->weight;

		steering->setLinear(steering->getLinear() + currentSteering->getLinear() * weight);

		steering->setAngular(steering->getAngular() + currentSteering->getAngular() * weight);
	}

	return steering;
}

void BlendedSteering::addBehavior(Steering* _newBehavior, float _weight)
{
	BlendedSteeringBehavior* newBehavior = new BlendedSteeringBehavior(_newBehavior, _weight);

	mBehaviors.push_back(newBehavior);
}

bool BlendedSteering::removeBehavior(int _index)
{
	return false;
}

bool BlendedSteering::removeBehavior(Steering* _behavior)
{
	return false;
}