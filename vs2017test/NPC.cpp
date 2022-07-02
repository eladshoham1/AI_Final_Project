#include "NPC.h"

NPC::NPC()
{
}

NPC::NPC(Point position)
{
	this->position = position;
	this->pCurrentState = nullptr;
	this->isMoving = false;
	this->hp = MAX_HP;
}

NPC::~NPC()
{
}

void NPC::setTarget(Point target, MapCell targetMapCell)
{
	this->target = target;
	this->targetMapCell = targetMapCell;
}

void NPC::insertToGrays(vector<Cell*>& grays, Cell* pCell)
{
	int index = 0;

	for (Cell* ptr : grays) {
		if (pCell->getF() < ptr->getF())
		{
			grays.insert(grays.begin() + index, pCell);
			return;
		}
		index++;
	}

	grays.push_back(pCell);
}

void NPC::checkNeighbor(int** maze, vector<Cell*>& grays, Cell* ps, Cell* pCurrent, int row, int col)
{
	if (maze[row][col] == this->targetMapCell)
	{
		// healteh storage found
	}
	else // paint this neighbor GRAY
	{
		Cell* pCell = new Cell(row, col, pCurrent, 0, this->target.getX(), this->target.getY());
		pCell->computeH();
		pCell->computeF();
		cout << "the target is: " << target.getX() << " " << target.getY() << endl;
		insertToGrays(grays, pCell);
	}
}

void NPC::goToTarget(int** maze)
{
	Cell* pCurrent;
	int row, col;

	vector<Cell*> grays;
	Cell *ps = new Cell(this->position.getX(), this->position.getY(), nullptr, 0, this->target.getX(), this->target.getY());
	grays.push_back(ps);

	if (!grays.empty())
	{
		pCurrent = *(grays.begin());
		grays.erase(grays.begin());

		row = pCurrent->getRow();
		col = pCurrent->getCol();
		//maze[row][col] = BLACK;
		// now scan all the white [or target] neighbors and add them (if it's not a target) to Grays
		// check UP
		if (maze[row + 1][col] == SPACE || maze[row + 1][col] == this->targetMapCell)
			checkNeighbor(maze, grays, ps, pCurrent, row + 1, col);
		// check DOWN
		if (maze[row - 1][col] == SPACE || maze[row - 1][col] == this->targetMapCell)
			checkNeighbor(maze, grays, ps, pCurrent, row - 1, col);
		// check LEFT
		if (maze[row][col - 1] == SPACE || maze[row][col - 1] == this->targetMapCell)
			checkNeighbor(maze, grays, ps, pCurrent, row, col - 1);
		// check RIGHT
		if (maze[row][col + 1] == SPACE || maze[row][col + 1] == this->targetMapCell)
			checkNeighbor(maze, grays, ps, pCurrent, row, col + 1);
	}
}

/*void NPC::play()
{
	if (atHome)
	{
		hp += 0.5;
		// check if the NPC should do something else
		if (hp >= MAX_HP)
			pCurrentState->Transform(this);
	}
	else // not at home
	{
		hp -= 0.2;
		// check if the NPC should do something else
		if (hp <= MAX_HP * 0.2 && !goingHome) // 20% of full HP
			pCurrentState->Transform(this);

	}

	if (isMoving)
	{
		x += dx * SPEED;
		y += dy * SPEED;
		// check if the NPC should do something else
		if (fabs(x - targetX) < 1 && fabs(y - targetY) < 1)
			pCurrentState->Transform(this);
	}
	else if (!atHome)// not moving
	{
		if (isGettingWood)
		{
			numWood++;
			// check if the NPC should do something else
			if (numWood >= MAX_WOOD)
				pCurrentState->Transform(this);
		}
		else
		{
			numWood--;
			// check if the NPC should do something else
			if (numWood <= MIN_WOOD)
				pCurrentState->Transform(this);
		}
	}
}*/

/*void NPC::setDestination(Point target)
{
	double distance;
	this->target = target;
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	// [dx,dy] must be vector of length 1 to the direction to target
	dx = (targetX - x) / distance;
	dy = (targetY - y) / distance;

}*/
