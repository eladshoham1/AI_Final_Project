#include "Team.h"

Team::Team(int id)
{
	this->id = id;
}

Team::~Team()
{
	for (int i = 0; i < NUM_OF_SOLDIERS; i++)
		delete this->soldiers[i];
	delete this->support;
}

void Team::initTeam(int** maze, Room* room)
{
	int row, col, maxRow, minRow, maxCol, minCol;
	minRow = room->getCenter().getY() - room->getHeight() / 2;
	maxRow = room->getCenter().getY() + room->getHeight() / 2;
	minCol = room->getCenter().getX() - room->getWidth() / 2;
	maxCol = room->getCenter().getX() + room->getWidth() / 2;

	for (int i = 0; i < NUM_OF_SOLDIERS; i++)
	{
		row = minRow + (rand() % (maxRow - minRow));
		col = minCol + (rand() % (maxCol - minCol));
		this->soldiers[i] = new Soldier(Point(row, col));
		maze[row][col] = static_cast<MapCell>(this->id);
	}

	this->support = new Support(Point(row, col));
	maze[row][col] = static_cast<MapCell>(this->id + 1);
}

void Team::play(int** maze)
{
	for (int i = 0; i < NUM_OF_SOLDIERS; i++)
	{
		this->soldiers[i]->play(maze);
		if (this->soldiers[i]->getHP() < NPC::MAX_HP / 2)
			this->support->addSoldierWithLowHP(*this->soldiers[i]);
		if (this->soldiers[i]->getNumOfBullets() < 1 || this->soldiers[i]->getNumOfGrenades() < 1)
			this->support->addSoldierWithLowAmmo(*this->soldiers[i]);
	}
	this->support->play(maze);
}

void Team::show()
{
	for (int i = 0; i < NUM_OF_SOLDIERS; i++)
		this->soldiers[i]->show();
	this->support->show();
}
