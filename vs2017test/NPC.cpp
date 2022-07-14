#include "NPC.h"
#include "Support.h"

NPC::NPC()
{
}

NPC::NPC(const Point& position, int teamId, int** maze, double** securityMap)
{
	this->setPosition(position);
	this->pCurrentState = nullptr;
	this->teamId = teamId;
	this->isMoving = false;
	this->hp = MAX_HP;
	this->dead = false;
	this->maze = maze;
	this->securityMap = securityMap;
	this->visibilityMap = new double*[MSZ];
	for (int i = 0; i < MSZ; i++)
		visibilityMap[i] = new double[MSZ] {0};
}

NPC::~NPC()
{
	for (int i = 0; i < MSZ; i++)
		delete this->visibilityMap[i];
	delete this->visibilityMap;
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

void NPC::checkNeighbor(priority_queue <Cell, vector<Cell>, CompareCells>& pq, vector <Cell>& grays, vector <Cell>& blacks, Cell* pCurrent, int row, int col)
{
	vector<Cell>::iterator it_gray;
	vector<Cell>::iterator it_black;
	double cost = this->securityMap[row][col];

	// who can be the neighbor
	if ((row == this->target.getX() && col == this->target.getY()) || this->maze[row][col] == SPACE)
	{
		// this is the neighbor
		Cell pn = Cell(row, col, pCurrent, pCurrent->getG() + cost, this->target.getX(), this->target.getY());

		// check the color of this neighbor
		it_black = find(blacks.begin(), blacks.end(), pn);
		if (it_black != blacks.end()) // it was found i.e. it is black
			return;
		// white
		it_gray = find(grays.begin(), grays.end(), pn);
		if (it_gray == grays.end()) // it wasn't found => it is white
		{
			grays.push_back(pn); // paint it gray
			pq.push(pn);
		}
		else // it is gray
		{
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

void NPC::setAsDead()
{
	this->dead = true;
	this->maze[this->position.getX()][this->position.getY()] = SPACE;
}

double NPC::distanceFromEnemy()
{
	if (this->closestEnemy != nullptr)
	{
		return this->position.euclideanDistance(this->closestEnemy->getPosition());
	}
	return 0.0;
}

bool NPC::isInDanger()
{
	if (this->closestEnemy != nullptr)
	{
		if (this->distanceFromEnemy() < 10)
		{
			if (dynamic_cast<Support*>(this) || this->hp < MAX_HP / 2.0)
			{
				return true;
			}
		}
	}
	return false;
}

bool NPC::isAtTarget()
{
	return abs(this->position.getX() - this->target.getX()) <= 1 && abs(this->position.getY() - this->target.getY()) <= 1;
}

void NPC::hit(double damage)
{
	if (damage > this->hp)
	{
		this->hp -= damage;
	}
	else
	{
		this->hp = 0.0;
	}
}

void NPC::goToTarget()
{
	int row, col;
	vector<Cell> grays, blacks;
	priority_queue<Cell, vector<Cell>, CompareCells> pq;
	vector<Cell>::iterator it_gray;
	Cell* pCurrent;
	Cell* pStart = new Cell(this->position.getX(), this->position.getY(), nullptr, 0, this->target.getX(), this->target.getY());

	grays.push_back(*pStart);
	pq.push(*pStart);
	delete pStart;

	while (!pq.empty())
	{
		pCurrent = new Cell(pq.top());
		pq.pop();

		if (pCurrent->getRow() == this->target.getX() && pCurrent->getCol() == this->target.getY())
		{
			if (pCurrent->getParent()->getParent() == nullptr)
			{
				if (this->maze[pCurrent->getRow()][pCurrent->getCol()] == SPACE)
				{
					this->maze[pCurrent->getParent()->getRow()][pCurrent->getParent()->getCol()] = SPACE;
					this->maze[pCurrent->getRow()][pCurrent->getCol()] = static_cast<MapCell>(this->teamId + (dynamic_cast<Support*>(this) ? 1 : 0));
					this->setPosition(Point(pCurrent->getRow(), pCurrent->getCol()));
					delete pCurrent->getParent();
					delete pCurrent;
				}
			}
			else
			{
				Cell* memory;
				while (pCurrent->getParent() != nullptr)
				{

					if (pCurrent->getParent()->getParent() == nullptr) // next step
					{
						this->maze[pCurrent->getParent()->getRow()][pCurrent->getParent()->getCol()] = SPACE;
						this->maze[pCurrent->getRow()][pCurrent->getCol()] = static_cast<MapCell>(this->teamId + (dynamic_cast<Support*>(this) ? 1 : 0));
						this->setPosition(Point(pCurrent->getRow(), pCurrent->getCol()));
						delete pCurrent->getParent();
						delete pCurrent;
						return;
					}
					memory = pCurrent;
					pCurrent = pCurrent->getParent();
					delete memory;
				}
			}
		}
		else
		{
			blacks.push_back(*pCurrent);
			it_gray = find(grays.begin(), grays.end(), *pCurrent);
			if (it_gray != grays.end()) // current was found
				grays.erase(it_gray); // removed from grays
			// now check the neighbors of current
			row = pCurrent->getRow();
			col = pCurrent->getCol();
			if (row > 0) // UP
				this->checkNeighbor(pq, grays, blacks, pCurrent, row - 1, col);
			if (row < MSZ - 1) // DOWN
				this->checkNeighbor(pq, grays, blacks, pCurrent, row + 1, col);
			if (col < MSZ - 1) // RIGHT
				this->checkNeighbor(pq, grays, blacks, pCurrent, row, col + 1);
			if (col > 0) //LEFT
				this->checkNeighbor(pq, grays, blacks, pCurrent, row, col - 1);
		}
	}
}

void NPC::play()
{
	this->pCurrentState->transform(this);
	if (this->isMoving)
	{
		this->goToTarget();
	}
}
