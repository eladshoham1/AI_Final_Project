#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include "glut.h"
#include "Definitions.h"
#include "Team.h"
#include "Room.h"
#include "Cell.h"
#include "CompareCells.h"
#include "Grenade.h"

using namespace std;

class Map
{
private:
	static constexpr int NUM_OF_TEAMS = 2;
	int** maze;
	Team* teams[NUM_OF_TEAMS];
	double** securityMap;
	double** visibilityMap;
	Room* rooms;
	bool underConstruction;
	int r1;
	int r2;
	Bullet* pBullet;
	Grenade* pGrenade;

	void initMap();

public:
	Map();
	Map(const char* fileName);
	~Map();
	int** getMaze() const { return this->maze; }
	double** getSecurityMap() const { return this->securityMap; }
	double** getVisibilityMap() const { return this->visibilityMap; }
	Room* getRooms() const { return this->rooms; }
	Bullet* getPBullet() const { return this->pBullet; }
	Grenade* getPGrenade() const { return this->pGrenade; }
	bool hasOverlap(int w, int h, int x, int y, int index);
	void setupRooms();
	void saveMapToFile(const char* fileName);
	void checkNeighbor(int row, int col, Cell* pcurrent, priority_queue <Cell, vector<Cell>, CompareCells>&pq, vector<Cell> &grays, vector<Cell> &blacks);
	void restorePath(Cell* ps);
	void digPath(int index1, int index2);
	void digPassages();
	void createVisibilityMap();
	void createSecurityMap();
	void showMaze();
	void showStartAndTarget();
	void play();
	friend ostream& operator<<(ostream& os, const Map& map);
	friend istream& operator>>(istream& in, Map& map);
};
