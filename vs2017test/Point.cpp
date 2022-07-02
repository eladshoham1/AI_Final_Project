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
