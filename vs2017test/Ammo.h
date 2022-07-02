#pragma once
#include "Point.h"

class Ammo
{
protected:
	Point position;

public:
	Ammo();
	Ammo(Point position);
	~Ammo();

	virtual void show() = 0;
};

