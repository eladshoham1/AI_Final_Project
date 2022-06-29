#pragma once
#include "State.h"

class ReloadMagazine : public State
{
public:
	ReloadMagazine();
	~ReloadMagazine();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};

