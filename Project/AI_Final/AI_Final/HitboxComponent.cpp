#include "HitboxComponent.h"
#include "Defines.h"
#include "GameApp.h"
#include "DebugLine.h"
#include "KinematicUnit.h"
#include "Sprite.h"

HitboxComponent::HitboxComponent(KinematicUnit* _unit, Vector2D const & _offset): Component(HITBOX), 
	mpUnit(_unit), mOffset(_offset)
{
	Vector2D size = _unit->getSprite()->getSize();

	mWidth = size.getX();
	mHeight = size.getY();

	createBounds(_unit->getPosition() + _offset);
}


HitboxComponent::HitboxComponent(KinematicUnit* _unit, float _width, float _height, Vector2D const & _offset): Component(HITBOX), 
	mpUnit(_unit), mWidth(_width), mHeight(_height), mOffset(_offset)
{
	createBounds(mpUnit->getPosition() + _offset);
}

HitboxComponent::HitboxComponent(HitboxComponent* _otherBox): Component(HITBOX)
{
	mpUnit = _otherBox->mpUnit;
	mWidth = _otherBox->mWidth;
	mHeight = _otherBox->mHeight;

	mPositionA = _otherBox->mPositionA;

	createBounds(mPositionA);

}


HitboxComponent::~HitboxComponent()
{}


bool HitboxComponent::checkCollision(HitboxComponent* _otherBox) // Checks if another hitbox has collided with it
{

	if (checkInBounds(_otherBox->getULCorner()))
	{
		return true;
	}
	else if (checkInBounds(_otherBox->getURCorner()))
	{
		return true;
	}
	else if (checkInBounds(_otherBox->getBLCorner()))
	{
		return true;
	}
	else if (checkInBounds(_otherBox->getBRCorner()))
	{
		return true;
	}

	return false;
}


bool HitboxComponent::checkInBounds(Vector2D &_point) // checks if a point has collided with the hitbox
{
	// Position A ---------------------- Position B
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	// Position C ---------------------- Position D

	if (mPositionA.getX() <= _point.getX() && _point.getX() <= mPositionB.getX())
	{
		if (mPositionC.getY() <= _point.getY() && _point.getY() <= mPositionA.getY())
		{
			return true;
		}
	}

	return false;
}


void HitboxComponent::createBounds(Vector2D const & _position)
{
	// Position A ---------------------- Position B
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	//			|						|
	// Position C ---------------------- Position D

	mPositionA.setX(_position.getX());
	mPositionA.setY(_position.getY());

	mPositionB.setX(mPositionA.getX() + mWidth);
	mPositionB.setY(mPositionA.getY());

	mPositionC.setX(mPositionA.getX());
	mPositionC.setY(mPositionA.getY() + mHeight);

	mPositionD.setX(mPositionA.getX() + mWidth);
	mPositionD.setY(mPositionA.getY() +   mHeight);
}


void HitboxComponent::update()
{
	updateBounds(mpUnit->getPosition() + mOffset);
}


void HitboxComponent::updateBounds(Vector2D const & _position)//creates new hitbox if the unit has moved since the last frame
{
	if (mPositionA != _position)
	{
		createBounds(_position);
	}

	DEBUG->drawRequest(new DebugLine(mPositionA, mPositionB));
	DEBUG->drawRequest(new DebugLine(mPositionA, mPositionC));
	DEBUG->drawRequest(new DebugLine(mPositionC, mPositionD));
	DEBUG->drawRequest(new DebugLine(mPositionB, mPositionD));
}


Vector2D HitboxComponent::getULCorner()
{
	return mPositionA;
}


Vector2D HitboxComponent::getURCorner()
{
	return mPositionB;
}


Vector2D HitboxComponent::getBLCorner()
{
	return mPositionC;
}


Vector2D HitboxComponent::getBRCorner()
{
	return mPositionD;
}