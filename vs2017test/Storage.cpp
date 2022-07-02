#include "Storage.h"

Storage::Storage(const Point& position)
{
	this->position = position;
	this->amount = INITIAL_AMOUNT;
}

Storage::~Storage()
{
}

int Storage::supply(int amount)
{
	int availableAmount = 0;

	if (!this->isEmpty())
	{
		if (amount >= this->amount)
		{
			availableAmount = amount;
			this->amount -= amount;
		}
		else
		{
			availableAmount = this->amount;
			this->amount = 0;
		}
	}

	return availableAmount;
}

void Storage::store(int amount)
{
	this->amount += amount;
}
