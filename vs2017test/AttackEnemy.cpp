#include "AttackEnemy.h"
#include "Soldier.h"
#include "Support.h"

AttackEnemy::AttackEnemy()
{
}

AttackEnemy::~AttackEnemy()
{
}

void AttackEnemy::transform(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		NPC* closestEnemy = soldier->getClosestEnemy();
		if (closestEnemy != nullptr)
		{
			MapCell mapCell = static_cast<MapCell>(closestEnemy->getTeamId() + dynamic_cast<Support*>(closestEnemy) ? 1 : 0);
			soldier->setTarget(closestEnemy->getPosition(), mapCell);
		}
	}
}

void AttackEnemy::onEnter(NPC* pn)
{
}

void AttackEnemy::onExit(NPC* pn)
{
}
