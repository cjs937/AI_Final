#pragma once
#include "Trackable.h"
#include <vector>
#include <iostream>

class GraphicsBuffer;
struct Ray;

struct DebugObject : public Trackable
{
public:
	DebugObject(bool _shouldDelete = true):deleteThisFrame(_shouldDelete) {};
	virtual ~DebugObject() {};

	virtual void draw(GraphicsBuffer* _backBuffer) = 0;

	bool deleteThisFrame;
};

class DebugSystem : public Trackable
{
public:
	DebugSystem();
	~DebugSystem();

	static void log(std::string _message, std::ostream & _stream = std::cout);

	void update();
	void drawRequest(DebugObject* _object);
	void draw(GraphicsBuffer* _backBuffer);
	void toggle();
	void toggle(bool _isOn);

	bool isActive() { return mIsActive; };

private:
	std::vector<DebugObject*> mObjectsThisFrame;

	bool mIsActive;

	void drawPaths();

};