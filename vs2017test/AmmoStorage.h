#pragma once
#include "Storage.h"

class AmmoStorage : public Storage
{
private:
	static constexpr int INITIAL_AMOUNT = 500;

public:
	AmmoStorage(const Point& position);
	~AmmoStorage();
};

