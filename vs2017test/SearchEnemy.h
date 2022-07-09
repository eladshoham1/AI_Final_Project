#pragma once
#include "State.h"
#include "GoToSafePlace.h"
#include "AttackEnemy.h"

class SearchEnemy : public State
{
public:
	SearchEnemy();
	~SearchEnemy();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
