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
enum ComponentType;

class Sprite;
class GraphicsBuffer;
class Component;
class HitboxComponent;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

enum UnitType
{
	//NONE = -1,
	PLAYER,
	AI,
	BOMB,
	EXPLOSION,
	NUM_TYPES
};

struct KUInitData
{
	KUInitData(UnitType _type, int _ID, Sprite* _pSprite, const Vector2D& _position, float _orientation, const Vector2D& _velocity, float _rotationVel, float _maxVelocity = 1.0f, float _maxAcceleration = 1.0f);

	~KUInitData();

	UnitType type;
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
	virtual ~KinematicUnit();

	//Update function for units that don't need to update any steering behaviors
	static void staticKUUpdate(KinematicUnit* _unit);

	//getters and setters
	UnitType getType() { return mType; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	void setVelocity( const Vector2D& velocity ){ mVelocity = velocity; };
	int getID() { return mUnitID; };
	Sprite* getSprite() { return mpSprite; };
	Vector2D getCenterPosition();
	Steering* getSteering() { return mpCurrentSteering; };
	bool isDeleting() { return mDeleting; };
	void markForDeletion() { mDeleting = true; }


	//Returns component based on type, otherwise returns NULL
	Component* getComponent(ComponentType _type);
	HitboxComponent* getHitbox();
	void addComponent(Component* _newComponent);
	virtual void setNewOrientation();//face the direction you are moving
	
	//draw yourself to the indicated buffer
	void draw( GraphicsBuffer* pBuffer );
	//move according to the current velocities and update velocities based on current Steering
	virtual void update(float time) override;

	//Handle collision with other units. Overriden by children that need it
	virtual void handleCollision(UnitType _colliderType) {};
private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	float mMaxVelocity;
	int mUnitID;
	UnitType mType;

	//If a unit is being deleted, they will be marked so different systems can know
	bool mDeleting;

protected:
	std::vector<Component*> mComponents;
	void setSteering( Steering* pSteering );

};