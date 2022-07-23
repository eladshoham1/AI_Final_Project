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
	if (pn->isAtTarget())
	{
		if (pn->scanAreaForEnemyGrenades())
		{
			pn->setCurrentState(new GoToSafePlace());
			//pn->getCurrentState()->onEnter(pn);
		}
		else
		{
			if (soldier)
			{
				if (!soldier->hasLoadedBullets() && soldier->hasBulletsInStock())
				{
					soldier->setCurrentState(new ReloadBullets());
					//soldier->getCurrentState()->onEnter(soldier);
				}
			}
			else if (support)
			{
				support->setCurrentState(new SupplyToSoldier());
				//support->getCurrentState()->onEnter(support);
			}
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
