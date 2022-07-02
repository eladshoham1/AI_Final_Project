#pragma once
#include "Storage.h"

class HealthStorage : public Storage
{
public:
	HealthStorage(const Point& position);
	~HealthStorage();
};
