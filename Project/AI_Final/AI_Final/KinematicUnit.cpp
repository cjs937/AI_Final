#include "Defines.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "Steering.h"
#include "Component.h"
using namespace std;

Steering gNullSteering( gZeroVector2D, 0.0f );


KUInitData::KUInitData(int _ID, Sprite* _pSprite, const Vector2D& _position, float _orientation, const Vector2D& _velocity, float _rotationVel, float _maxVelocity = 1.0f, float _maxAcceleration = 1.0f)
	:ID(_ID), pSprite(_pSprite), position(_position), orientation(_orientation), velocity(_velocity), rotationVel(_rotationVel), maxVelocity(_maxVelocity), maxAcceleration(_maxAcceleration)
{}

KUInitData::~KUInitData() {}


KinematicUnit::KinematicUnit(KUInitData const & _data )
:Kinematic( _data.position, _data.orientation, _data.velocity, _data.rotationVel )
,mpSprite(_data.pSprite)
,mpCurrentSteering(NULL)
,mMaxVelocity(_data.maxVelocity)
,mMaxAcceleration(_data.maxAcceleration)
,mUnitID(_data.ID)
{
}

KinematicUnit::~KinematicUnit()
{
	for (int i = 0; i < mComponents.size(); ++i)
	{
		delete mComponents[i];

		mComponents[i] = NULL;
	}

	delete mpCurrentSteering;
}

void KinematicUnit::draw( GraphicsBuffer* pBuffer )
{
	mpSprite->draw( *pBuffer, mPosition.getX(), mPosition.getY(), mOrientation );
}

void KinematicUnit::update(float time)
{
	for (int i = 0; i < mComponents.size(); ++i)
		mComponents[i]->update(time);

	Steering* steering;
	if( mpCurrentSteering != NULL )
	{

		steering = mpCurrentSteering->getSteering();

		//Steering* collisionSteering;

		//collisionSteering =	CollisionSystem::checkUnitCollision(this, steering);

		//if (collisionSteering != NULL)
		//	steering = collisionSteering;
	}
	else
	{
		steering = &gNullSteering;
	}

	if( steering->shouldApplyDirectly() )
	{
		//not stopped
		if( getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED )
		{
			setVelocity( steering->getLinear() );
			setOrientation( steering->getAngular() );
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity( 0.0f );
		steering->setAngular( 0.0f );
	}

	//move the unit using current velocities
	Kinematic::update( time );
	//calculate new velocities
	calcNewVelocities( *steering, time, mMaxVelocity, 25.0f );
	//move to oposite side of screen if we are off
	GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	//setNewOrientation();
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering( Steering* pSteering )
{
 	delete mpCurrentSteering;

	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{ 
	mOrientation = getOrientationFromVelocity( mOrientation, mVelocity ); 
}

//void KinematicUnit::seek(const Vector2D &target)
//{
//	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering( this, target );
//	setSteering( pSeekSteering );
//}
//
//void KinematicUnit::arrive(const Vector2D &target)
//{
//	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering( this, target );
//	setSteering( pArriveSteering );
//}
//
//void KinematicUnit::wander()
//{
//	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering( this );
//	setSteering( pWanderSteering );
//}
//
//void KinematicUnit::dynamicSeek( KinematicUnit* pTarget )
//{
//	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget);
//	setSteering( pDynamicSeekSteering );
//}
//
//void KinematicUnit::dynamicFlee( KinematicUnit* pTarget )
//{
//	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering( this, pTarget, true );
//	setSteering( pDynamicSeekSteering );
//}
//
//void KinematicUnit::dynamicArrive( KinematicUnit* pTarget )
//{
//	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering( this, pTarget);
//	setSteering( pDynamicArriveSteering );
//}

void KinematicUnit::addComponent(Component* _newComponent)
{
	mComponents.push_back(_newComponent);
}