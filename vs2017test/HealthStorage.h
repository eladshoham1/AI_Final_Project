#pragma once
#include "Storage.h"

class HealthStorage : public Storage
{
private:
	static constexpr int INITIAL_AMOUNT = 250;

public:
	HealthStorage(const Point& position);
	~HealthStorage();
};
