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
	Team* enemyTeam;
	int id;
	int npcTurn;

public:
	Team() = delete;
	Team(int id);
	~Team();

	Soldier** getSoldiers() { return this->soldiers; }
	Support* getSupport() { return this->support; }
	Team* getEnemyTeam() { return this->enemyTeam; }
	void setEnemyTeam(Team* enemyTeam) { this->enemyTeam = enemyTeam; }
	int getId() { return this->id; }
	void initTeam(int** maze, double** securityMap, Room* room, Team* enemyTeam);
	bool theyAllDeads();
	void play(int** maze);
	void nextTurn();
	void show();
};
