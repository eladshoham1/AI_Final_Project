#pragma once
#include <vector>
#include <queue>
#include "Definitions.h"
#include "Point.h"
#include "Cell.h"
#include "CompareCells.h"
#include "State.h"

using namespace std;

class NPC
{
public:
	static constexpr double MAX_HP = 100.0;

protected:
	Point position;
	Point target;
	State* pCurrentState;
	int teamId;
	bool isMoving;
	double hp;
	bool dead;
	int** maze;
	double** securityMap;
	double** visibilityMap;
	vector<NPC*> enemies;

	void insertToGrays(vector<Cell*>& grays, Cell* pCell);
	void checkNeighbor(priority_queue <Cell, vector<Cell>, CompareCells>& pq, vector<Cell>& grays, vector<Cell>& blacks, Cell* pCurrent, int row, int col);

public:
	NPC();
	NPC(const Point& position, int teamId, int** maze, double** securityMap);
	virtual ~NPC();

	Point getPosition() { return this->position; }
	void setPosition(const Point& position) { this->position = position; }
	Point getTarget() { return this->target; }
	void setTarget(const Point& target);
	State* getCurrentState() const { return this->pCurrentState; }
	void setCurrentState(State* pCurrentState);
	double getHP() const { return this->hp; }
	int getTeamId() { return this->teamId; }
	vector<NPC*> getEnemies() const { return this->enemies; }
	void setEnemies(const vector<NPC*>& enemies) { this->enemies = enemies; }
	double hpLack() const { return MAX_HP - this->hp; }
	bool hpLastThanHalf() { return this->hp < MAX_HP / 2.0; }
	bool getIsMoving() const { return this->isMoving; }
	void setIsMoving(bool isMoving) { this->isMoving = isMoving; }
	NPC* findEnemy();
	void setVisibilityMapToZero();
	void supplyHP(int hp);
	void setAsDead();
	bool isDead() { return this->dead; }
	double distanceFromEnemy();
	bool isInDanger();
	bool isAtTarget();
	void hit(double damage);
	void goToTarget();
	bool goToSafePosition();
	bool scanAreaForEnemyGrenades() const;
	void play();
	virtual void show() = 0;
};