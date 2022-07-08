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
	static constexpr double MAX_HP = 100.0;

protected:
	Point position;
	Point target;
	MapCell targetMapCell;
	State* pCurrentState;
	State* pInterruptedState;
	bool isMoving;
	double hp;
	int teamId;
	NPC* closestEnemy;

	void insertToGrays(vector<Cell*>& grays, Cell* pCell);
	void checkNeighbor(int** maze, double** securityMap, priority_queue <Cell, vector<Cell>, CompareCells>& pq, vector <Cell>& grays, vector <Cell>& blacks, Cell* pCurrent, int row, int col);

public:
	NPC();
	NPC(const Point& position, int teamId);
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
	int getTeamId() { return this->teamId; }
	NPC* getClosestEnemy() const { return this->closestEnemy; }
	void setClosestEnemy(NPC* closestEnemy) { this->closestEnemy = closestEnemy; }
	double hpLack() const { return MAX_HP - this->hp; }
	bool getIsMoving() const { return this->isMoving; }
	bool isInDanger() { return this->hp < MAX_HP / 2.0; }
	bool isDead() { return this->hp == 0; }
	bool isAtTarget();
	void hit(double damage);
	void goToTarget(int** maze, double** securityMap);
	void play(int** maze, double** securityMap);
	virtual void show() = 0;
};