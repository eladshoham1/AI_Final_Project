#pragma once
#include <iostream>
#include "Point.h"

using namespace std;

class Storage
{
protected:
	Point position;
	int amount;

public:
	Storage(const Point& position, int amount);
	virtual ~Storage();

	Point getPosition() const { return this->position; }
	void setPosition(Point position) { this->position = position; }
	int getAmount() const { return this->amount; }
	bool isEmpty() const { return this->amount == 0.0; }
	int supply(int amount);
	void store(int amount);
};
