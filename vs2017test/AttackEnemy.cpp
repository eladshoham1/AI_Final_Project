#include "AttackEnemy.h"
#include "Soldier.h"

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
		if (soldier->isInDanger() || !soldier->hasLoadedBullets())
		{
			soldier->setCurrentState(new GoToSafePlace());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else if (!soldier->isEnemyVisible())
		{
			soldier->setCurrentState(new SearchEnemy());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else
		{
			soldier->attack();
		}
	}
}

void AttackEnemy::onEnter(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		soldier->setIsMoving(false);
	}
}

void AttackEnemy::onExit(NPC* pn)
{
}
