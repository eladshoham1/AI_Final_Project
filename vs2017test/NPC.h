#pragma once
#include "Point.h"
#include "State.h"
#include "AttackEnemy.h"

class NPC
{
public:
	static constexpr int MAX_HP = 100;
protected:
	Point position;
	Point target;
	State* pCurrentState;
	State* pInterruptedState;
	bool isMoving;
	double hp;

public:
	NPC();
	NPC(Point position);
	virtual ~NPC();

	State* getCurrentState() const { return this->pCurrentState; }
	void setCurrentState(State* ps) { this->pCurrentState = ps; }
	State* getInterruptedState() const { return this->pInterruptedState; }
	void setInterruptedState(State* ps) { this->pInterruptedState = ps; }
	double getHP() const { return this->hp; }
	bool getIsMoving() const { return this->isMoving; }
	virtual void play(int** maze) = 0;
	virtual void show() = 0;
};
