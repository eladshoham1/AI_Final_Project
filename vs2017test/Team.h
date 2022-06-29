#pragma once
#include <iostream>
#include "Warrior.h"
#include "Squire.h"

using namespace std;

class Team
{
private:
	Warrior *warriors;
	Squire *pSquire;
public:
	Team();
	~Team();

	void play();
};
