#pragma once

#include "Kinematic.h"
#include "Steering.h"
#include <vector>
/*KinematicUnit - a unit that is derived from the Kinematic class.  Adds behaviors and max speeds and a current Steering.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class Sprite;
class GraphicsBuffer;
class Component;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

//minmimum forward speed a unit has to have inorder to rotate 
//(keeps unit from spinning in place after stopping


struct KUInitData
{
	KUInitData(int _ID, Sprite* _pSprite, const Vector2D& _position, float _orientation, const Vector2D& _velocity, float _rotationVel, float _maxVelocity = 1.0f, float _maxAcceleration = 1.0f);

	~KUInitData();

	int ID;
	Sprite* pSprite;
	Vector2D position;
	float orientation;
	Vector2D velocity;
	float rotationVel;
	float maxVelocity;
	float maxAcceleration;
};

const float MIN_VELOCITY_TO_TURN_SQUARED = 1.0f;

class KinematicUnit: public Kinematic
{
public:
	KinematicUnit( KUInitData const & _data );
	~KinematicUnit();

	//getters and setters
	void setTarget( const Vector2D& target ) { mTarget = target; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	void setVelocity( const Vector2D& velocity ){ mVelocity = velocity; };
	int getID() { return mUnitID; };
	Sprite* getSprite() { return mpSprite; };
	Vector2D getCenterPosition();
	Steering* getSteering() { return mpCurrentSteering; };
	void addComponent(Component* _newComponent);
	virtual void setNewOrientation();//face the direction you are moving
	
	//draw yourself to the indicated buffer
	void draw( GraphicsBuffer* pBuffer );
	//move according to the current velocities and update velocities based on current Steering
	virtual void update(float time) override;

private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	Vector2D mTarget;//used only for Kinematic seek and arrive
	float mMaxVelocity;
	float mMaxAcceleration;
	int mUnitID;

protected:
	std::vector<Component*> mComponents;
	void setSteering( Steering* pSteering );

};