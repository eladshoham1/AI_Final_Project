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

/*void NPC::checkNeighbor(int** maze, vector<Cell*>& grays, Cell* ps, Cell* pCurrent, int row, int col)
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
}*/

void NPC::checkNeighbor(int** maze, double** securityMap, priority_queue <Cell, vector<Cell>, CompareCells>& pq, vector <Cell>& grays, vector <Cell>& blacks, Cell* pCurrent, int row, int col)
{
	vector<Cell>::iterator it_gray;
	vector<Cell>::iterator it_black;
	double cost = securityMap[row][col];

	// who can be the neighbor
	if ((row == this->target.getX() && col == this->target.getY()) || maze[row][col] == SPACE)
	{
		// this is the neighbor
		Cell pn = Cell(row, col, pCurrent, pCurrent->getG() + cost, this->target.getX(), this->target.getY());

		// check the color of this neighbor
		it_black = find(blacks.begin(), blacks.end(), pn);
		if (it_black != blacks.end()) // it was found i.e. it is black
			return;
		cout << "row: " << row << " col: " << col << " targetRow: " << this->target.getX() << " targetCol: " << this->target.getY() << endl;
		// white
		it_gray = find(grays.begin(), grays.end(), pn);
		if (it_gray == grays.end()) // it wasn't found => it is white
		{
			grays.push_back(pn); // paint it gray
			pq.push(pn);
		}
		else // it is gray
		{
			//   new F       ?      old F
			if (pn.getF() < it_gray->getF()) // then update it (F of neighbor)
			{
				// we need to update it in two places:
				// 1. in vector grays
				it_gray->setG(pn.getG());
				it_gray->setF(pn.getF());
				// 2. in PQ
				// to update a Cell in pq we need to remove it from pq, to update it and to push it back
				vector<Cell> tmp;
				Cell tmpCell;
				do
				{
					if (pq.empty())
					{
						cout << "ERROR! PQ is empty in update PQ\n";
						exit(EXIT_FAILURE);
					}
					tmpCell = pq.top();
					pq.pop();
					if (!(tmpCell == (pn))) // do not copy the Cell we were looking for to tmp! 
						tmp.push_back(tmpCell);
				} while (!(tmpCell == (pn)));
				// now we are out of do-while because we have found the neighbor in PQ. So change it to *pn.
				pq.push(pn);
				// now push back all the elements that are in tmp
				while (!tmp.empty())
				{
					pq.push(tmp.back());
					tmp.pop_back();
				}
			}
		}
	}
}

void NPC::goToTarget(int** maze, double** securityMap)
{
	int row, col;
	vector <Cell> grays;
	vector <Cell> blacks;
	priority_queue <Cell, vector<Cell>, CompareCells> pq;

	Cell* pstart = new Cell(this->position.getX(), this->position.getY(), nullptr, 0, this->target.getX(), this->target.getY());
	Cell* pCurrent;
	// initializes grays and pq
	grays.push_back(*pstart);
	pq.push(*pstart);
	delete pstart;
	vector<Cell>::iterator it_gray;

	while (!pq.empty())
	{
		pCurrent = new Cell(pq.top());
		pq.pop();

		// If current is actually a target then we stop A*	
		if (pCurrent->getRow() == this->target.getX() && pCurrent->getCol() == this->target.getY()) // then it is target	
		{ //in this case there cannot be a better path to target!!!		
			return;
		}

		// paint current black
		blacks.push_back(*pCurrent);
		it_gray = find(grays.begin(), grays.end(), *pCurrent);
		if (it_gray != grays.end()) // current was found
			grays.erase(it_gray); // and removed from grays
		// now check the neighbors of current
		row = pCurrent->getRow();
		col = pCurrent->getCol();
		// try to go UP (row -1)
		if (row > 0) // we can go UP
			this->checkNeighbor(maze, securityMap, pq, grays, blacks, pCurrent, this->position.getX() - 1, this->position.getY());

		if (row < MSZ - 1) // DOWN
			this->checkNeighbor(maze, securityMap, pq, grays, blacks, pCurrent, this->position.getX() + 1, this->position.getY());

		if (col < MSZ - 1) // RIGHT
			this->checkNeighbor(maze, securityMap, pq, grays, blacks, pCurrent, this->position.getX(), this->position.getY() + 1);

		if (col > 0) //LEFT
			this->checkNeighbor(maze, securityMap, pq, grays, blacks, pCurrent, this->position.getX(), this->position.getY() - 1);
	}
}

/*void NPC::goToTarget(int** maze)
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
}*/

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
