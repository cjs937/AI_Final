#pragma once

#include <fstream>
#include <vector>
#include "Trackable.h"

class Vector2D;

const int CLEAR_VALUE = 0;
const int BLOCKING_VALUE = 1;

class GraphicsBuffer;
class Sprite;

class Grid:public Trackable
{
public:
	Grid( int pixelWidth, int pixelHeight, int squareSize );
	~Grid();

	int getSquareIndexFromPixelXY( int x, int y ) const;

	int getValueAtIndex( int index ) const;
	int getValueAtPixelXY( int x, int y ) const;
	void setValueAtIndex( int index, int value );
	void setValueAtPixelXY( int x, int y, int value );
	Vector2D getULCornerOfSquare( int index ) const;
	Vector2D getCenterOfSquare(int _index) const;

	//accessors
	int getPixelWidth() const { return mPixelWidth; };
	int getPixelHeight() const { return mPixelHeight; };
	int getGridWidth() const { return mGridWidth; };
	int getGridHeight() const { return mGridHeight; };
	int getSquareSize() const { return mSquareSize; };

	//get adjacent grid square indices
	std::vector<int> getAdjacentIndices( int theSquareIndex ) const;

	void save(std::ofstream& file);
	void loadGrid(std::ifstream& file);

	void draw(GraphicsBuffer* _backBuffer);
	void drawLevel(Vector2D _pos, Sprite* _spriteToDraw, GraphicsBuffer* _backBuffer);

private:
	int* mpValues;
	int mPixelWidth;
	int mPixelHeight;
	int mSquareSize;
	int mGridWidth;
	int mGridHeight;
};