#pragma once
#include <iostream>
#include "Soldier.h"
#include "Support.h"
#include "Room.h"

using namespace std;

class Team
{
public:
	static constexpr int NUM_OF_SOLDIERS = 2;

private:
	Soldier *soldiers[NUM_OF_SOLDIERS];
	Support *support;
	int id;
	int npcTurn;

public:
	Team() = delete;
	Team(int id);
	~Team();

	Soldier** getSoldiers() { return this->soldiers; }
	Support* getSupport() { return this->support; }
	int getId() { return this->id; }
	void initTeam(int** maze, Room* room);
	bool theyAllDeads();
	void play(int** maze, double** securityMap);
	void nextTurn();
	void show();
};
