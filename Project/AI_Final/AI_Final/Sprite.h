#pragma once

#include <string>

/*Sprite - a logical portion of a GraphicsBuffer.

Dean Lawson
Champlain College
2011
*/
#include <allegro5/allegro.h>

#include "Trackable.h"

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	Sprite( GraphicsBuffer* pBuffer, float srcX, float srcY, float width, float height );
	~Sprite();

	//draw the contents of the sprite to a GraphicsBuffer - may be rotated
	void draw( GraphicsBuffer& dest, float dx, float dy, float rotationInRadians = 0, int flags = 0 );
	int getWidth() { return mWidth; };
	int getHeight() { return mHeight; };

	void drawScaled(GraphicsBuffer& dest, float dx, float dy, float dw, float dh, int flags);// needed for the walls and such
private:

	ALLEGRO_BITMAP* mpBitmap;//subBitmap based off the GraphicsBuffer object is contructed with
	int mWidth;
	int mHeight;
};