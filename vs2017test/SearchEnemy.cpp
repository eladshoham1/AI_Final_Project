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
		if (soldier->isInDanger() || !soldier->hasLoadedBullets())
		{
			soldier->setCurrentState(new GoToSafePlace());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else if (soldier->isEnemyVisible())
		{
			soldier->setCurrentState(new AttackEnemy());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else
		{
			NPC* closestEnemy = soldier->getClosestEnemy();
			if (closestEnemy != nullptr)
			{
				MapCell mapCell = static_cast<MapCell>(closestEnemy->getTeamId() + dynamic_cast<Support*>(closestEnemy) ? 1 : 0);
				soldier->setTarget(closestEnemy->getPosition(), mapCell);
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
