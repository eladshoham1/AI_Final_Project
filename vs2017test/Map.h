#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include "glut.h"
#include "Definitions.h"
#include "Cell.h"
#include "CompareCells.h"
#include "Room.h"
#include "Team.h"
#include "Support.h"
#include "Grenade.h"

using namespace std;

class Map
{
private:
	static constexpr int NUM_OF_ROOMS = 8;
	static constexpr int NUM_OF_TEAMS = 2;
	int** maze;
	double** securityMap;
	double** visibilityMap;
	Room* rooms[NUM_OF_ROOMS];
	Team* teams[NUM_OF_TEAMS];
	Grenade* pGrenade;
	int teamTurn;

	void initMap();

public:
	Map();
	Map(const char* fileName);
	~Map();
	int** getMaze() const { return this->maze; }
	double** getSecurityMap() const { return this->securityMap; }
	double** getVisibilityMap() const { return this->visibilityMap; }
	Room** getRooms() { return this->rooms; }
	bool hasOverlap(int width, int height, int x, int y, int index);
	void setupRooms();
	void saveMapToFile(const char* fileName);
	void checkNeighbor(int row, int col, Cell* pcurrent, priority_queue <Cell, vector<Cell>, CompareCells>&pq, vector<Cell> &grays, vector<Cell> &blacks);
	void restorePath(Cell* ps);
	void digPath(int index1, int index2);
	void digPassages();
	void placeTeams();
	void createVisibilityMap();
	void createSecurityMap();
	void findClosestEnemy(NPC* npc);
	void findClosestHealthStorage(Support* support);
	void findClosestAmmoStorage(Support* support);
	void showMaze();
	bool play();
	void nextTurn();
	friend ostream& operator<<(ostream& os, const Map& map);
	friend istream& operator>>(istream& in, Map& map);
};
