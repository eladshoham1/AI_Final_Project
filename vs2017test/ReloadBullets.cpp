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
		if (soldier->hasBulletsInStock())
		{
			//cout << "soldier->loadBullets();" << endl;
			soldier->loadBullets();
			//cout << "loadBullets: " << soldier->getLoadedBullets() << endl;
		}
		else
		{
			soldier->setWaitingForSupport(true);
			//cout << "soldier->setWaitingForSupport(true);" << endl;
			/*if (!soldier->isInDanger() && soldier->hasLoadedBullets())
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
				soldier->setCurrentState(new GoToSafePlace());
				soldier->getCurrentState()->onEnter(soldier);
			}*/
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
