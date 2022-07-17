#pragma once
#include "State.h"
#include "SupplyToSoldier.h"

class GoToStorage : public State
{
public:
	GoToStorage();
	~GoToStorage();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};