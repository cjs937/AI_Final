#pragma once

#include <allegro5/allegro.h>
#include <vector>
#include <map>
#include "Trackable.h"
#include "GraphicsSystem.h"

class Grid;
class GraphicsBuffer;
class Sprite;

class LevelEditor :public Trackable
{
public:
	LevelEditor(Grid* pGrid);
	~LevelEditor();

	void addColor(int index, const ALLEGRO_COLOR& color);
	void removeAllEntriesOfColor(const ALLEGRO_COLOR& color);
	void removeEntry(int index, const ALLEGRO_COLOR& color);
	void setModified() { mDirty = true; };
	void draw(GraphicsBuffer& dest);
	void clear();

	//void addSprite(int index, const Sprite* sprite);
	//void removeAllEntriesOfSprite(const Sprite* sprite);
	//void removeEntry(int index, const ALLEGRO_COLOR& color);
	//void setModified() { mDirty = true; };
	//void draw(GraphicsBuffer& dest);
	//void clear();
private:
	void refresh();

	Grid* mpGrid;
	//key is color, vector contains all indices to be colored that color
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare > mColormap;
	//changing the map functionality to work with sprites
	

	bool mDirty;
};
