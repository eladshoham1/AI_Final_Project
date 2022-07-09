#pragma once
#include "Point.h"

class Ammo
{
protected:
	double x, y;

public:
	Ammo();
	Ammo(double x, double y);
	~Ammo();

	double getX() { return this->x; }
	void setX(double x) { this->x = x; }
	double getY() { return this->y; }
	void setY(double y) { this->y = y; }
	virtual void show() = 0;
};

