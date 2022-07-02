#pragma once
#include "Point.h"

class Storage
{
protected:
	static constexpr int INITIAL_AMOUNT = 1000;
	Point position;
	int amount;

public:
	Storage(const Point& position);
	virtual ~Storage();

	Point getPosition() const { return this->position; }
	void setPosition(Point position) { this->position = position; }
	int getAmount() const { return this->amount; }
	bool isEmpty() const { return this->amount == 0; }
	int supply(int amount);
	void store(int amount);
};
