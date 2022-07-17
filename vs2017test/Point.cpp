#include "Point.h"

Point::Point()
{
}

Point::Point(int x, int y)
{
	this->setPoint(x, y);
}

Point::~Point()
{
}

void Point::setPoint(int x, int y)
{
	this->setX(x);
	this->setY(y);
}

double Point::euclideanDistance(const Point& target)
{
	return this->euclideanDistance(target.getX(), target.getY());
}

double Point::euclideanDistance(int x, int y)
{
	return sqrt(pow(this->x - x, 2) + pow(this->y - y, 2));
}

bool Point::operator==(const Point& other)
{
	return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point& other)
{
	return !(*this == other);
}

ostream & operator<<(ostream& os, const Point& point)
{
	if (typeid(os) == typeid(ofstream))
		os << point.x << " " << point.y;

	return os;
}

istream & operator>>(istream& in, Point& point)
{
	if (typeid(in) == typeid(ifstream))
	{
		ifstream& inFile = dynamic_cast<ifstream&>(in);
		in >> point.x >> point.y;
	}

	return in;
}
