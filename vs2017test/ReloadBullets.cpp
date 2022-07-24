#include "ReloadBullets.h"
#include "Soldier.h"

ReloadBullets::ReloadBullets()
{
}

ReloadBullets::~ReloadBullets()
{
}

void ReloadBullets::transform(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		if (soldier->needToReloadBullets())
		{
			if (soldier->hasBulletsInStock())
				soldier->loadBullets();
			else
			{
				if (soldier->hasSupporterAlive())
					soldier->setWaitingForSupport(true);
				else
				{
					if (soldier->scanAreaForEnemyGrenades())
						soldier->setCurrentState(new GoToSafePlace());
				}
			}
		}
		else
		{
			if (soldier->isEnemyVisible() || soldier->isUnderAttack())
				soldier->setCurrentState(new AttackEnemy());
			else
				soldier->setCurrentState(new SearchEnemy());
		}
	}
}

void ReloadBullets::onEnter(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		soldier->setIsMoving(false);
	}
}

void ReloadBullets::onExit(NPC* pn)
{
}
