#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "Component.h"

class KinematicUnit;

class HitboxComponent : public Component
{
private:

	KinematicUnit* mpUnit;

	Vector2D mPositionA;
	Vector2D mPositionB;
	Vector2D mPositionC;
	Vector2D mPositionD;

	Vector2D mOffset;

	float mWidth;
	float mHeight;

	bool mIsColliding;

public:

	HitboxComponent(KinematicUnit* _unit, Vector2D const & _offset = Vector2D(0, 0));
	HitboxComponent(KinematicUnit* _unit, float _width, float _height, Vector2D const & _offset = Vector2D(0, 0));
	HitboxComponent(HitboxComponent* const _otherBox);
	~HitboxComponent();

	bool checkCollision(HitboxComponent* const _otherBox);
	bool checkInBounds(Vector2D &_point);

	void createBounds(Vector2D const & _position);
	void updateBounds(Vector2D const & _position);
	virtual void update() override;
	Vector2D getULCorner();
	Vector2D getURCorner();
	Vector2D getBLCorner();
	Vector2D getBRCorner();

};