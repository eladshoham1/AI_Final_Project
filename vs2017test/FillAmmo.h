#pragma once
#include "State.h"

class FillAmmo : public State
{
public:
	FillAmmo();
	~FillAmmo();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
