#pragma once
#include "State.h"

class AttackEnemy : public State
{
public:
	AttackEnemy();
	~AttackEnemy();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
