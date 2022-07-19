#include "SearchEnemy.h"
#include "Soldier.h"
#include "Support.h"

SearchEnemy::SearchEnemy()
{
}

SearchEnemy::~SearchEnemy()
{
}

void SearchEnemy::transform(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		if (soldier->scanAreaForEnemyGrenades() || soldier->getLoadedBullets() == 0)
		{
			soldier->setCurrentState(new GoToSafePlace());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else if (soldier->isEnemyVisible())
		{ 
			if (soldier->getHP() > NPC::MAX_HP / 2.0 && soldier->hasLoadedBullets())
			{
				soldier->setCurrentState(new AttackEnemy());
				soldier->getCurrentState()->onEnter(soldier);
			}
		}
		else
		{
			if (soldier->getClosestEnemy() != nullptr)
			{
				soldier->setTarget(soldier->getClosestEnemy()->getPosition());
			}
		}
	}
}

void SearchEnemy::onEnter(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		soldier->setWaitingForSupport(false);
		soldier->setIsMoving(true);
	}
}

void SearchEnemy::onExit(NPC* pn)
{
}
