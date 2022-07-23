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

void Team::initTeam(int** maze, double** securityMap, Room* room, Team* enemyTeam)
{
	int row, col, maxRow, minRow, maxCol, minCol;
	minRow = room->getCenter().getY() - room->getHeight() / 2;
	maxRow = room->getCenter().getY() + room->getHeight() / 2;
	minCol = room->getCenter().getX() - room->getWidth() / 2;
	maxCol = room->getCenter().getX() + room->getWidth() / 2;

	for (int i = 0; i < NUM_OF_SOLDIERS + 1; i++)
	{
		row = minRow + (rand() % (maxRow - minRow));
		col = minCol + (rand() % (maxCol - minCol));
		if (i < NUM_OF_SOLDIERS)
		{
			this->soldiers[i] = new Soldier(Point(row, col), this->id, maze, securityMap);
			maze[row][col] = static_cast<MapCell>(this->id);
		}
		else
		{
			this->support = new Support(Point(row, col), this->soldiers, this->id, maze, securityMap);
			maze[row][col] = static_cast<MapCell>(this->id + 1);
		}
	}

	this->setEnemyTeam(enemyTeam);
}

bool Team::theyAllDeads()
{
	for (int i = 0; i < NUM_OF_SOLDIERS; i++)
	{
		if (!this->soldiers[i]->isDead())
		{
			return false;
		}
	}
	return true;
}

void Team::play(int** maze)
{
	int i;
	for (i = 0; i < NUM_OF_SOLDIERS; i++)
	{
		if (i == this->npcTurn)
		{
			if (this->support->isDead())
			{
				this->soldiers[i]->setSupporterAlive(false);
			}
			this->soldiers[i]->play();
		}
	}
	if (i == this->npcTurn)
	{
		this->support->play();
	}
	this->nextTurn();
}

void Team::nextTurn()
{
	if (this->npcTurn < NUM_OF_SOLDIERS)
	{
		this->npcTurn++;
	}
	else
	{
		this->npcTurn = 0;
	}
}

void Team::show()
{
	for (int i = 0; i < NUM_OF_SOLDIERS; i++)
		this->soldiers[i]->show();
	this->support->show();
}
