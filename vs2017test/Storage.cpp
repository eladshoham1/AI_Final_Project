#include "Storage.h"

Storage::Storage(const Point& position, int amount)
{
	this->position = position;
	this->amount = amount;
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
