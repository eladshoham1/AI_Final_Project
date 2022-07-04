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

void Support::play(int** maze, double** securityMap)
{
	this->setTarget(Point(position.getX() + 5, position.getY() + 4), WALL);
	this->goToTarget(maze, securityMap);
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
