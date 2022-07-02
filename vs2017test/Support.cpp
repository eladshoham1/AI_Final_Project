#include "Support.h"

Support::Support()
{
}

Support::Support(Point position) : NPC(position)
{
}

Support::~Support()
{
}

void Support::play(int** maze)
{
	this->goToTarget(maze);
}

void Support::show()
{
}

void Support::addSoldierWithLowHP(const Soldier& soldier)
{
	this->waitingForHP.push(soldier);
}

void Support::addSoldierWithLowAmmo(const Soldier& soldier)
{
	this->waitingForAmmo.push(soldier);
}
