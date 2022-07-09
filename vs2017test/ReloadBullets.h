#pragma once
#include "State.h"

class ReloadBullets : public State
{
public:
	ReloadBullets();
	~ReloadBullets();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};

