#include "Map.h"

Map::Map()
{
	initMap();
	setupRooms();
	placeTeams();
	createSecurityMap();
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
		saveMapToFile(fileName);
	}
	placeTeams();
	createSecurityMap();
}

Map::~Map()
{
	for (int i = 0; i < MSZ; i++)
		delete this->maze[i];
	delete this->maze;

	for (int i = 0; i < MSZ; i++)
		delete this->securityMap[i];
	delete this->securityMap;

	for (int i = 0; i < NUM_OF_TEAMS; i++)
		delete this->teams[i];
}

void Map::initMap()
{
	this->maze = new int*[MSZ];
	for (int i = 0; i < MSZ; i++)
		this->maze[i] = new int[MSZ] {0};

	this->securityMap = new double*[MSZ];
	for (int i = 0; i < MSZ; i++)
		this->securityMap[i] = new double[MSZ] {0};

	for (int i = 0; i < NUM_OF_TEAMS; i++)
		this->teams[i] = new Team((int)SOLDIER_TEAM_ONE + i * 2);

	this->teamTurn = 0;
}

// checks for overlapping with rooms of lower indices
bool Map::hasOverlap(int width, int height, int x, int y, int index)
{
	bool overlaps = false;
	int i;
	int dx, dy, gap = 4;

	for (i = 0; i < index && !overlaps; i++)
	{
		dx = abs(rooms[i]->getCenter().getX() - x);
		dy = abs(rooms[i]->getCenter().getY() - y);
		if (dx < width / 2 + rooms[i]->getWidth() / 2 + gap && dy < height / 2 + rooms[i]->getHeight() / 2 + gap)
			overlaps = true;
	}
	return overlaps;
}

void Map::setupRooms()
{
	int width, height, x, y;
	for (int i = 0; i < NUM_OF_ROOMS; i++)
	{
		do
		{
			width = 8 + rand() % 25;
			height = 8 + rand() % 25;
			x = 2 + width / 2 + rand() % (MSZ - 4 - width);
			y = 2 + height / 2 + rand() % (MSZ - 4 - height);
		} while (hasOverlap(width, height, x, y, i));
		this->rooms[i] = new Room(width, height, Point(x, y));
		this->rooms[i]->initRoom(this->maze);
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
	double cost, cheap = 0.1, expensive = 0.8;
	vector <Cell>::iterator itrb;
	vector <Cell>::iterator itrg;

	cost = this->maze[row][col] == SPACE ? cheap : expensive;

	// create neighbor cell
	Cell* pn = new Cell(row, col, pcurrent, pcurrent->getG() + cost, pcurrent->getRow(), pcurrent->getCol());
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
	Cell* startingCell = new Cell(this->rooms[index1]->getCenter().getY(), this->rooms[index1]->getCenter().getX(),
		nullptr, 0, this->rooms[index2]->getCenter().getY(), this->rooms[index2]->getCenter().getX());

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
		if (pcurrent->getRow() == this->rooms[index2]->getCenter().getY() && pcurrent->getCol() == this->rooms[index2]->getCenter().getX())
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

	for (i = 0; i < NUM_OF_ROOMS; i++)
	{
		for (j = i + 1; j < NUM_OF_ROOMS; j++)
			digPath(i, j);
	}
}

void Map::placeTeams()
{
	for (int i = 0; i < NUM_OF_TEAMS; i++)
		this->teams[i]->initTeam(this->maze, this->securityMap, this->rooms[rand() % NUM_OF_ROOMS]);
}

void Map::createSecurityMap()
{
	int numOfSimulations = 500;
	double damage = 0.01;
	int i;
	Grenade* g;
	
	for (i = 0; i < numOfSimulations; i++)
	{
		g = new Grenade(rand() % MSZ, rand() % MSZ);
		g->simulateExplosion(this->maze, this->securityMap, damage);
	}
}

void Map::findClosestEnemy(NPC* npc)
{
	NPC* closestEnemy = nullptr;
	for (int i = 0; i < NUM_OF_TEAMS; i++)
	{
		if (npc->getTeamId() != this->teams[i]->getId())
		{
			for (int j = 0; j < Team::NUM_OF_SOLDIERS; j++)
			{
				if (!this->teams[i]->getSoldiers()[j]->isDead())
				{
					if (closestEnemy == nullptr || npc->getPosition().euclideanDistance(this->teams[i]->getSoldiers()[j]->getPosition()) <
						npc->getPosition().euclideanDistance(closestEnemy->getPosition()))
					{
						closestEnemy = this->teams[i]->getSoldiers()[j];
					}
				}
			}
		}
	}
	npc->setClosestEnemy(closestEnemy);
}

void Map::findClosestHealthStorage(Support* support)
{
	HealthStorage* closestHealthStorage = nullptr;
	for (int i = 0; i < NUM_OF_ROOMS; i++)
	{
		for (int j = 0; j < Room::NUM_OF_HEALTH_STORAGE; j++)
		{
			if (closestHealthStorage == nullptr || support->getPosition().euclideanDistance(this->rooms[i]->getHealthStorages()[j]->getPosition()) <
				support->getPosition().euclideanDistance(closestHealthStorage->getPosition()))
			{
				if (!this->rooms[i]->getHealthStorages()[j]->isEmpty())
				{
					closestHealthStorage = this->rooms[i]->getHealthStorages()[j];
				}
			}
		}
	}
	support->setClosestHealthStorage(closestHealthStorage);
}

void Map::findClosestAmmoStorage(Support* support)
{
	AmmoStorage* closestAmmoStorage = nullptr;
	for (int i = 0; i < NUM_OF_ROOMS; i++)
	{
		for (int j = 0; j < Room::NUM_OF_HEALTH_STORAGE; j++)
		{
			if (closestAmmoStorage == nullptr || support->getPosition().euclideanDistance(this->rooms[i]->getAmmoStorages()[j]->getPosition()) <
				support->getPosition().euclideanDistance(closestAmmoStorage->getPosition()))
			{
				if (!this->rooms[i]->getAmmoStorages()[j]->isEmpty())
				{
					closestAmmoStorage = this->rooms[i]->getAmmoStorages()[j];
				}
			}
		}
	}
	support->setClosestAmmoStorage(closestAmmoStorage);
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
			case SPACE:
				glColor3d(1.0, 1.0, 1.0); // white
				break;
			case OBSTACLE:
				glColor3d(0.4, 0.4, 0.4); // gray
				break;
			case AMMO:
				glColor3d(0.1, 0.7, 0.4);
				break;
			case HEALTH:
				glColor3d(0.2, 0.6, 0.6);
				break;
			case SOLDIER_TEAM_ONE:
				glColor3d(0.1, 0.1, 0.3);
				break;
			case SUPPORT_TEAM_OME:
				glColor3d(0.3, 0.3, 0.5);
				break;
			case SOLDIER_TEAM_TWO:
				glColor3d(0.6, 0.6, 0.1);
				break;
			case SUPPORT_TEAM_TWO:
				glColor3d(0.8, 0.8, 0.3);
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
	
	for (int i = 0; i < NUM_OF_TEAMS; i++)
		this->teams[i]->show();
}

bool Map::play()
{
	for (int i = 0; i < NUM_OF_TEAMS; i++)
	{
		if (!this->teams[i]->theyAllDeads())
		{
			if (i == this->teamTurn)
			{
				this->teams[i]->play();
				for (int j = 0; j < Team::NUM_OF_SOLDIERS; j++)
				{
					this->findClosestEnemy(this->teams[i]->getSoldiers()[j]);
				}
				this->findClosestEnemy(this->teams[i]->getSupport());
				this->findClosestHealthStorage(this->teams[i]->getSupport());
				this->findClosestAmmoStorage(this->teams[i]->getSupport());
				this->nextTurn();
			}
			for (int j = 0; j < NUM_OF_ROOMS; j++)
			{
				HealthStorage** healthStorages = this->rooms[j]->getHealthStorages();
				for (int k = 0; k < Room::NUM_OF_HEALTH_STORAGE; k++)
				{
					if (healthStorages[k]->isEmpty())
					{
						this->maze[healthStorages[k]->getPosition().getX()][healthStorages[k]->getPosition().getY()] = OBSTACLE;
					}
				}
				AmmoStorage** ammoStorages = this->rooms[j]->getAmmoStorages();
				for (int k = 0; k < Room::NUM_OF_AMMO_STORAGE; k++)
				{
					if (ammoStorages[k]->isEmpty())
					{
						this->maze[ammoStorages[k]->getPosition().getX()][ammoStorages[k]->getPosition().getY()] = OBSTACLE;
					}
				}
			}
		}
		else
		{
			cout << "Team " << (i + 1) << " won" << endl;
			return false;
		}
	}
	return true;
}

void Map::nextTurn()
{
	if (this->teamTurn < NUM_OF_TEAMS - 1)
	{
		this->teamTurn++;
	}
	else
	{
		this->teamTurn = 0;
	}
}

ostream& operator<<(ostream& os, const Map& map)
{
	int** mapMaze = map.getMaze();
	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
			os << mapMaze[i][j] << " ";
	}
	for (int i = 0; i < Map::NUM_OF_ROOMS; i++)
		os << *map.rooms[i] << endl;

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
		for (int i = 0; i < Map::NUM_OF_ROOMS; i++)
		{
			map.rooms[i] = new Room(inFile);
			map.rooms[i]->initRoom(map.getMaze());
		}
	}
	return in;
}
