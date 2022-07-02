#pragma once
#include <queue>
#include "NPC.h"
#include "Soldier.h"

class Support : public NPC
{
private:
	queue<Soldier> waitingForHP;
	queue<Soldier> waitingForAmmo;

public:
	Support();
	Support(Point position);
	~Support();

	void play(int** maze);
	void show();
	void addSoldierWithLowHP(const Soldier& soldier);
	void addSoldierWithLowAmmo(const Soldier& soldier);
};

