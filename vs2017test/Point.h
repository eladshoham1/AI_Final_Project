#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Point
{
private:
	int x, y;
public:
	Point();
	Point(int x, int y);
	~Point();

	int getX() const { return this->x; }
	void setX(int x) { this->x = x; }
	int getY() const { return this->y; }
	void setY(int y) { this->y = y; }
	void setPoint(int x, int y);
	friend ostream & operator<<(ostream& os, const Point& point);
	friend istream & operator>>(istream& in, Point& point);
};
