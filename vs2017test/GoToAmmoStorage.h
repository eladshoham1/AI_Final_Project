#pragma once
#include "State.h"

class GoToAmmoStorage : public State
{
public:
	GoToAmmoStorage();
	~GoToAmmoStorage();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};