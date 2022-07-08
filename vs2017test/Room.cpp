#include "Room.h"

Room::Room(int width, int height, Point&& center)
{
	this->width = width;
	this->height = height;
	this->center = center;
}

Room::Room(ifstream& in)
{
	in >> *this;
}

Room::~Room()
{
}

void Room::addObjects(int** maze, int numOfObjects, MapCell object)
{
	int row, col, minRow, maxRow, minCol, maxCol;
	minRow = this->center.getY() - this->height / 2;
	maxRow = this->center.getY() + this->height / 2;
	minCol = this->center.getX() - this->width / 2;
	maxCol = this->center.getX() + this->width / 2;

	for (int i = 0; i < numOfObjects; i++)
	{
		row = minRow + (rand() % (maxRow - minRow));
		col = minCol + (rand() % (maxCol - minCol));
		if (object == AMMO)
		{
			this->ammoStorages[i] = new AmmoStorage(Point(row, col));
		}
		else if (object == HEALTH)
		{
			this->healthStorages[i] = new HealthStorage(Point(row, col));
		}
		maze[row][col] = object;
	}
}

void Room::initRoom(int** maze)
{
	for (int i = this->center.getY() - this->height / 2; i <= this->center.getY() + this->height / 2; i++)
		for (int j = this->center.getX() - this->width / 2; j <= this->center.getX() + this->width / 2; j++)
			maze[i][j] = SPACE;

	this->addObjects(maze, rand() % ((int)ceil(height * width * OBSTACLES_PRECENTAGE)) + MIN_OBSTACLES, OBSTACLE);
	this->addObjects(maze, NUM_OF_AMMO_STORAGE, AMMO);
	this->addObjects(maze, NUM_OF_HEALTH_STORAGE, HEALTH);
}

ostream & operator<<(ostream& os, const Room& room)
{
	if (typeid(os) == typeid(ofstream))
		os << room.width << " " << room.height << " " << room.center;

	return os;
}

istream & operator>>(istream& in, Room& room)
{
	if (typeid(in) == typeid(ifstream))
	{
		ifstream& inFile = dynamic_cast<ifstream&>(in);
		in >> room.width >> room.height >> room.center;
	}

	return in;
}
