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

	return this->support->isDead();
}

void Team::play(int** maze)
{
	int i, j;
	for (i = 0; i < NUM_OF_SOLDIERS; i++)
	{
		if (i == this->npcTurn)
		{
			if (this->support->isDead())
			{
				this->soldiers[i]->setSupporterAlive(false);
			}
			this->soldiers[i]->play();
			/*if (this->enemyTeam)
			{
				if (this->soldiers[i]->getPBullet())
				{
					Point* point = this->soldiers[i]->getPBullet()->move(maze);
					if (point)
					{
						for (j = 0; j < NUM_OF_SOLDIERS; j++)
						{
							if (*point == this->enemyTeam->getSoldiers()[j]->getPosition())
							{
								Point shootingPosition = this->soldiers[i]->getPBullet()->getShootingPosition();
								double distance = point->euclideanDistance(shootingPosition);
								this->enemyTeam->getSoldiers()[j]->hit(rand() % 10 + distance);
							}
						}
					}
				}
			}*/
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
