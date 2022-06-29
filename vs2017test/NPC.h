#pragma once
#include "State.h"

class State;

class NPC
{
private:
	/*double x, y;
	double targetX, targetY;
	double dx, dy; // vector to the target
	double numWood;
	double hp;
	bool isMoving, isGettingWood, atHome, goingHome;
	State* pCurrentState;
	State* pInterruptedState;*/

public:
	NPC();
	~NPC();
	//NPC(double x, double y);
	/*void DoSomeThing(); // kind of MAIN function
	void setIsMoving(bool value) { isMoving = value; }
	void setDestination(double destX, double destY);
	void setIsGettingWood(bool value) { isGettingWood = value; }
	void setCurrentState(State* ps) { pCurrentState = ps; }
	State* getCurrentState() { return pCurrentState; }
	double getHP() { return hp; }
	void setAtHome(bool value) { atHome = value; }
	void setGoingHome(bool value) { goingHome = value; }
	void setInterruptedState(State* ps) { pInterruptedState = ps; }
	State* getInterruptedState() { return pInterruptedState; }
	void DrawMe();*/
};
