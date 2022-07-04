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

public:
	Team() = delete;
	Team(int id);
	~Team();

	void initTeam(int** maze, Room* room);
	void play(int** maze, double** securityMap);
	void show();
};
