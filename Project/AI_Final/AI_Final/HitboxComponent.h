#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class HitboxComponent : public Trackable
{
private:

	Vector2D mPositionA;
	Vector2D mPositionB;
	Vector2D mPositionC;
	Vector2D mPositionD;

	Vector2D mOffset;

	float mWidth;
	float mHeight;

	bool mIsTrigger;
	bool mIsColliding;

public:

	HitboxComponent(float _width, float _height, Vector2D const & _position, bool _isTrigger, Vector2D const & _offset = Vector2D(0, 0));
	HitboxComponent(HitboxComponent* const _otherBox);
	~HitboxComponent();

	bool checkCollision(HitboxComponent* const _otherBox);
	bool checkInBounds(Vector2D &_point);

	void createBounds(Vector2D const & _position);
	void update(Vector2D const & _position);

	Vector2D getULCorner();
	Vector2D getURCorner();
	Vector2D getBLCorner();
	Vector2D getBRCorner();

	bool isTrigger() { return mIsTrigger; };

	void setIsTrigger(bool _isTrigger);
};