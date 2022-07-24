#include "GoToSafePlace.h"
#include "Soldier.h"
#include "Support.h"

GoToSafePlace::GoToSafePlace()
{
}

GoToSafePlace::~GoToSafePlace()
{
}

void GoToSafePlace::transform(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (support->hpLastThanHalf())
		{
			support->takeHealth();
		}
	}
	if (pn->isAtTarget())
	{
		if (pn->scanAreaForEnemyGrenades())
			pn->setCurrentState(new GoToSafePlace());
		else
		{
			if (soldier)
			{
				if (!soldier->hasLoadedBullets() && soldier->hasBulletsInStock())
					soldier->setCurrentState(new ReloadBullets());
				else if (soldier->isEnemyVisible() || soldier->isUnderAttack())
					soldier->setCurrentState(new AttackEnemy());
				else
					soldier->setCurrentState(new SearchEnemy());
			}
			else if (support)
				support->setCurrentState(new SupplyToSoldier());
		}
	}
}

void GoToSafePlace::onEnter(NPC* pn)
{
	pn->setIsMoving(true);
	pn->goToSafePosition();
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		soldier->setWaitingForSupport(soldier->isInDanger() && !soldier->hasBulletsInStock());
	}
}

void GoToSafePlace::onExit(NPC* pn)
{
}
