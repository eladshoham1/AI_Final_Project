#include "Map.h"

Map::Map()
{
	initMap();
}

Map::Map(const char* fileName)
{
	initMap();
	ifstream inFile(fileName);

	if (!inFile.fail() && inFile.peek() != EOF)
	{
		inFile >> *this;
		inFile.close();
	}
	else
	{
		setupRooms();
		digPassages();
		/*for (int i = 0; i < MSZ; i++) {
			for (int j = 0; j < MSZ; j++) {
				cout << this->maze[i][j] << " ";
			}
		}*/
		saveMapToFile(fileName);
	}
}

Map::~Map()
{
	for (int i = 0; i < MSZ; i++)
		delete this->maze[i];
	delete this->maze;

	for (int i = 0; i < MSZ; i++)
		delete this->securityMap[i];
	delete this->securityMap;

	for (int i = 0; i < MSZ; i++)
		delete this->visibilityMap[i];
	delete this->visibilityMap;

	for (int i = 0; i < NUM_OF_TEAMS; i++)
		delete this->teams[i];
	delete this->teams;

	delete this->rooms;
}

void Map::initMap()
{
	this->maze = new int*[MSZ];
	for (int i = 0; i < MSZ; i++)
		this->maze[i] = new int[MSZ] {0};

	this->securityMap = new double*[MSZ];
	for (int i = 0; i < MSZ; i++)
		this->securityMap[i] = new double[MSZ] {0};

	this->visibilityMap = new double*[MSZ];
	for (int i = 0; i < MSZ; i++)
		this->visibilityMap[i] = new double[MSZ] {0};

	this->rooms = new Room[NUM_ROOMS];
}

// checks for overlapping with rooms of lower indices
bool Map::hasOverlap(int w, int h, int x, int y, int index)
{
	bool overlaps = false;
	int i;
	int dx, dy, gap = 4;

	for (i = 0; i < index && !overlaps; i++)
	{
		dx = abs(rooms[i].getCenterX() - x);
		dy = abs(rooms[i].getCenterY() - y);
		if (dx < w / 2 + rooms[i].getWidth() / 2 + gap && dy < h / 2 + rooms[i].getHeight() / 2 + gap)
			overlaps = true;
	}
	return overlaps;
}

void Map::setupRooms()
{
	int w, h, x, y;
	for (int r = 0; r < NUM_ROOMS; r++)
	{
		do
		{
			w = 8 + rand() % 25;
			h = 8 + rand() % 25;
			x = 2 + w / 2 + rand() % (MSZ - 4 - w);
			y = 2 + h / 2 + rand() % (MSZ - 4 - h);
		} while (hasOverlap(w, h, x, y, r));
		this->rooms[r].setWidth(w);
		this->rooms[r].setHeight(h);
		this->rooms[r].setCenterX(x);
		this->rooms[r].setCenterY(y);
		this->rooms[r].addMeToMaze(this->maze);
	}
}

void Map::saveMapToFile(const char* fileName)
{
	ofstream outFile(fileName, ios::trunc);

	if (!outFile.fail())
	{
		outFile << *this;
		outFile.close();
	}
}

// if the neighbor cell is white  (including target as wll) then add it to pq and paint it gray
// if it is black then do nothing
// if it is gray (it can be target as wll) check 2 cases:
//         1: if F of the new found neghbor isn't better (>=) then of the previously found cell then do notheing
//         2: if  F of the new found neghbor IS better (<) then we have to update the cell parameters!!!
void Map::checkNeighbor(int row, int col, Cell* pcurrent, priority_queue <Cell, vector<Cell>, CompareCells>&pq, vector<Cell> &grays, vector<Cell> &blacks)
{
	double cost, cheap = 0.1, expensive = 0.4;
	vector <Cell>::iterator itrb;
	vector <Cell>::iterator itrg;

	cost = this->maze[row][col] == SPACE ? cheap : expensive;

	// create neighbor cell
	Cell* pn = new Cell(row, col, pcurrent, pcurrent->getG() + cost, pcurrent->getTargetRow(), pcurrent->getTargetCol());
	// check color of theis cell
	itrb = find(blacks.begin(), blacks.end(), *pn);
	itrg = find(grays.begin(), grays.end(), *pn);

	// if it is white
	if (itrb == blacks.end() && itrg == grays.end())
	{
		pq.push(*pn);
		grays.push_back(*pn);
	}
	else  // it must be either gray or black
	{
		if (itrg != grays.end())
		{
			if (pn->getF() < itrg->getF()) // we have to update it
			{
				grays.erase(itrg);
				grays.push_back(*pn);
				// to update (find) pn in pq we need manually to extract all the cells that stand bfore pn in pq including pn
				// to update it and then to push all of them back to pq
				vector <Cell> tmp;
				while (!pq.empty() && !((*pn) == pq.top()))
				{
					tmp.push_back(pq.top());
					pq.pop();
				}
				if (pq.empty())
					cout << " neighbor wasn't found in pq \n";
				else // *pn is now at top of pq
				{
					pq.pop();
					pq.push(*pn);
					// move back to pq all the cells from tmp
					while (!tmp.empty())
					{
						pq.push(tmp.back());
						tmp.pop_back();
					}
				}
			}
		}
	}
}

void Map::restorePath(Cell* ps)
{
	while (ps->getParent() != nullptr)
	{
		if (this->maze[ps->getRow()][ps->getCol()] == WALL)
			this->maze[ps->getRow()][ps->getCol()] = SPACE;
		ps = ps->getParent();
	}
}

// creates path from rooms[index1] to rooms[index2] using A*
void Map::digPath(int index1, int index2)
{
	Cell* startingCell = new Cell(this->rooms[index1].getCenterY(), this->rooms[index1].getCenterX(),
		nullptr, 0, this->rooms[index2].getCenterY(), this->rooms[index2].getCenterX());

	Cell* pcurrent = nullptr;
	int currentRow, currentCol;

	priority_queue <Cell, vector<Cell>, CompareCells> pq;
	vector <Cell> grays;
	vector <Cell> blacks;

	vector <Cell>::iterator itr;

	// add Start Cell to pq and paint it gray
	pq.push(*startingCell);
	grays.push_back(*startingCell);

	// start A* . In our case pq shouldn't be empty because we should find the target before all the 
	// cells are over
	while (!pq.empty())
	{
		// pq is not empty so pick the top Cell
		pcurrent = new Cell(pq.top());
		// check if current is target
		if (pcurrent->getRow() == this->rooms[index2].getCenterY() && pcurrent->getCol() == this->rooms[index2].getCenterX())
		{
			restorePath(pcurrent);
			cout << "The path from room " << index1 << " to room " << index2 << " has been found\n";
			return;
		}
		// remove current from pq and paint it black (remove it from grays)
		pq.pop();
		blacks.push_back(*pcurrent);
		// remove it from grays
		itr = find(grays.begin(), grays.end(), *pcurrent); // Cell must have operator ==
		if (itr == grays.end()) // current cell wasn't found: ERROR
		{
			cout << "Error: current wasn't found in grays for room " << index1 << " to room " << index2 << endl;
			return;
		}
		grays.erase(itr);

		// now check the neighbor cells
		currentRow = pcurrent->getRow();
		currentCol = pcurrent->getCol();
		if (currentRow > 0) // UP
			checkNeighbor(currentRow - 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentRow < MSZ - 1) // DOWN
			checkNeighbor(currentRow + 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentCol > 0) // LEFT
			checkNeighbor(currentRow, currentCol - 1, pcurrent, pq, grays, blacks);
		if (currentCol < MSZ - 1) // RIGHT
			checkNeighbor(currentRow, currentCol + 1, pcurrent, pq, grays, blacks);
	} // while
	// We shouldn't reach this point normally
	cout << "Error: PQ is empty for room " << index1 << " to room " << index2 << endl;
}

void Map::digPassages()
{
	int i, j;

	for (i = 0; i < NUM_ROOMS; i++)
	{
		for (j = i + 1; j < NUM_ROOMS; j++)
			digPath(i, j);
	}
}

void Map::createVisibilityMap()
{
	this->pGrenade->simulateVisibility(maze, visibilityMap);
}

void Map::createSecurityMap()
{
	int num_simulations = 500;
	double damage = 0.001;
	int i;
	Grenade* g;

	for (i = 0; i < num_simulations; i++)
	{
		g = new Grenade(rand() % MSZ, rand() % MSZ);
		g->simulateExplosion(this->maze, this->securityMap, damage);
	}
}

void Map::showMaze()
{
	int i, j;

	for (i = 0; i < MSZ; i++)
	{
		for (j = 0; j < MSZ; j++)
		{
			// set color for cell (i,j)
			switch (this->maze[i][j])
			{
			case WALL:
				glColor3d(0.1, 0.1, 0.1); // dark gray
				break;
			case OBSTACLE:
				glColor3d(0.4, 0.4, 0.4); // gray
				break;
			case SPACE:
				double d = this->securityMap[i][j];
				double v = this->visibilityMap[i][j];
				glColor3d(1 - d - 0.5*v, 1 - d, 1 - d - 0.5*v); // white - security map value - visibility map value
				break;
			}// switch
			// now show the cell as plygon (square)
			glBegin(GL_POLYGON);
			glVertex2d(j, i); // left-bottom corner
			glVertex2d(j, i + 1); // left-top corner
			glVertex2d(j + 1, i + 1); // right-top corner
			glVertex2d(j + 1, i); // right-bottom corner
			glEnd();
		}// for
	}

	if (this->underConstruction)
		showStartAndTarget();

	if (this->pBullet != nullptr)
		this->pBullet->show();
	if (this->pGrenade != nullptr)
		this->pGrenade->show();
}

void Map::showStartAndTarget()
{
	int i, j;
	// start
	i = this->rooms[r1].getCenterY();
	j = this->rooms[r1].getCenterX();
	glColor3d(0, 0, 1); // blue
	glBegin(GL_POLYGON);
	glVertex2d(j, i); // left-bottom corner
	glVertex2d(j, i + 1); // left-top corner
	glVertex2d(j + 1, i + 1); // right-top corner
	glVertex2d(j + 1, i); // right-bottom corner
	glEnd();

	// target
	i = this->rooms[r2].getCenterY();
	j = this->rooms[r2].getCenterX();
	glColor3d(1, 0.7, 0); // orange
	glBegin(GL_POLYGON);
	glVertex2d(j, i); // left-bottom corner
	glVertex2d(j, i + 1); // left-top corner
	glVertex2d(j + 1, i + 1); // right-top corner
	glVertex2d(j + 1, i); // right-bottom corner
	glEnd();
}

void Map::play()
{
	for (int i = 0; i < NUM_OF_TEAMS; i++)
		teams[i]->play();
	/*if (this->underConstruction)
	{
		digPath(this->r1, this->r2);
		// prepare for the next A*
		this->r2++;
		if (this->r2 >= NUM_ROOMS)
		{
			this->r1++;
			this->r2 = this->r1 + 1;
			if (this->r1 + 1 >= NUM_ROOMS)
				this->underConstruction = false;
		}
	}
	// bullet
	if (this->pBullet != nullptr && this->pBullet->getIsMoving())
		this->pBullet->move(this->maze);
	if (this->pGrenade != nullptr && this->pGrenade->getIsExploded())
		this->pGrenade->exploding(this->maze);*/
}

ostream& operator<<(ostream& os, const Map& map)
{
	int** mapMaze = map.getMaze();
	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
			os << mapMaze[i][j] << " ";
	}
	return os;
}

istream& operator>>(istream& in, Map& map)
{
	if (typeid(in) == typeid(ifstream))
	{
		ifstream& inFile = dynamic_cast<ifstream&>(in);
		int** mapMaze = map.getMaze();
		for (int i = 0; i < MSZ; i++)
		{
			for (int j = 0; j < MSZ; j++)
				inFile >> mapMaze[i][j];
		}
	}
	return in;
}
