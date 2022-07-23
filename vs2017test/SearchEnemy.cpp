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
			soldier->setCurrentState(new GoToSafePlace());
		else if (soldier->isEnemyVisible())
		{
			if (!soldier->hpLastThanHalf() && soldier->hasLoadedBullets())
			{
				soldier->setCurrentState(new AttackEnemy());
			}
		}
		else
		{
			NPC* enemy = soldier->findEnemy();
			if (enemy)
			{
				soldier->setTarget(enemy->getPosition());
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
