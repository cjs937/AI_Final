#pragma once

#include "AIState.h"
#include <vector>
#include "GridPathfinder.h"

class Timer;

const float MAX_DISTANCE = 10000;

class AI_Pathfind : public AIState
{
	public:
		AI_Pathfind(AIUnit & _unit);
		~AI_Pathfind();
		
		virtual void onEnter() override;
		virtual State* update() override;
		
	private:
		Vector2D mDirection;
		Path mPath;
		Node* mpToNode;
		int mResetCheck;

		int mTo, mFrom, currentIndexPos;

		void getPath();

		Vector2D getNextDirection();
		Vector2D getDirectionFromIndex(Vector2D _unitPosition, int _index);
		bool mPathFound;
		void move();

};