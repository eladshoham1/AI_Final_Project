#pragma once
#include "State.h"
#include "GoToSoldier.h"

class GoToHealthStorage : public State
{
public:
	GoToHealthStorage();
	~GoToHealthStorage();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};