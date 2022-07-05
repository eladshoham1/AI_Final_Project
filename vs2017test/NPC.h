#pragma once
#include <vector>
#include <queue>
#include "Definitions.h"
#include "Point.h"
#include "Cell.h"
#include "CompareCells.h"
#include "State.h"
#include "AttackEnemy.h"

using namespace std;

class NPC
{
public:
	static constexpr int MAX_HP = 100;

protected:
	Point position;
	Point target;
	MapCell targetMapCell;
	State* pCurrentState;
	State* pInterruptedState;
	bool isMoving;
	double hp;

	void insertToGrays(vector<Cell*>& grays, Cell* pCell);
	void checkNeighbor(int** maze, double** securityMap, priority_queue <Cell, vector<Cell>, CompareCells>& pq, vector <Cell>& grays, vector <Cell>& blacks, Cell* pCurrent, int row, int col);

public:
	NPC();
	NPC(const Point& position);
	virtual ~NPC();

	Point getPosition() { return this->position; }
	void setPosition(const Point& position) { this->position = position; }
	Point getTarget() { return this->target; }
	MapCell getTargetMapCell() { return this->targetMapCell; }
	void setTarget(Point target, MapCell targetMapCell);
	State* getCurrentState() const { return this->pCurrentState; }
	void setCurrentState(State* ps) { this->pCurrentState = ps; }
	State* getInterruptedState() const { return this->pInterruptedState; }
	void setInterruptedState(State* ps) { this->pInterruptedState = ps; }
	double getHP() const { return this->hp; }
	bool getIsMoving() const { return this->isMoving; }
	bool isTarget() { return this->position == this->target; }
	void goToTarget(int** maze, double** securityMap);
	virtual void play(int** maze, double** securityMap) = 0;
	virtual void show() = 0;
};