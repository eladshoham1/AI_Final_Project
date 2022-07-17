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
		cout << soldier->getHP() << " " << soldier->getLoadedBullets() << endl;
		if (soldier->scanAreaForEnemyGrenades() || soldier->getLoadedBullets() == 0)
		{
			cout << "3333" << endl;
			soldier->setCurrentState(new GoToSafePlace());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else if (soldier->getHP() > 50 && soldier->getLoadedBullets() > 30)
		{
			cout << "4444" << endl;
			soldier->setCurrentState(new AttackEnemy());
			soldier->getCurrentState()->onEnter(soldier);
		}
		else
		{
			if (soldier->getLeader())
			{
				soldier->followLeader();
			}
			else
			{
				NPC* closestEnemy = soldier->getClosestEnemy();
				if (closestEnemy != nullptr)
				{
					soldier->setTarget(closestEnemy->getPosition());
				}
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
