#include "GoToSafePlace.h"
#include "Soldier.h"

GoToSafePlace::GoToSafePlace()
{
}

GoToSafePlace::~GoToSafePlace()
{
}

void GoToSafePlace::transform(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		if (!soldier->hasLoadedBullets()) {
			if (soldier->hasBulletsInStock())
			{
				soldier->setCurrentState(new ReloadBullets());
				soldier->getCurrentState()->onEnter(soldier);
			}
			else
			{
				soldier->setWaitingForSupport(true);
			}
		}
		else
		{
			if (!soldier->isInDanger())
			{
				if (soldier->isEnemyVisible())
				{
					soldier->setCurrentState(new AttackEnemy());
					soldier->getCurrentState()->onEnter(soldier);
				}
				else
				{
					soldier->setCurrentState(new SearchEnemy());
					soldier->getCurrentState()->onEnter(soldier);
				}
			}
			else
			{
				soldier->setWaitingForSupport(true);
			}
		}
	}
}

void GoToSafePlace::onEnter(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		soldier->setWaitingForSupport(soldier->isInDanger() && !soldier->hasBulletsInStock());
		soldier->setIsMoving(true);
	}
}

void GoToSafePlace::onExit(NPC* pn)
{
}
