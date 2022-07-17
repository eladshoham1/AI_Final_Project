#include "GoToStorage.h"
#include "Support.h"

GoToStorage::GoToStorage()
{
}

GoToStorage::~GoToStorage()
{
}

void GoToStorage::transform(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (!support->scanAreaForEnemyGrenades())
		{
			if (support->isAtTarget())
			{
				cout << "SupplyToSoldier1" << endl;
				support->takeHealthFromStorage();
				pn->setCurrentState(new SupplyToSoldier());
			}
			else
			{
				if (support->getHealth() < 25)
				{
					cout << "goToClosestHealthStorage" << endl;
					support->goToClosestHealthStorage();
				}
				else if (support->getAmmo() < 40)
				{
					cout << "goToClosestAmmoStorage" << endl;
					support->goToClosestAmmoStorage();
				}
				else
				{
					cout << "SupplyToSoldier2" << endl;
					support->takeHealthFromStorage();
					pn->setCurrentState(new SupplyToSoldier());
				}
			}
		}
		else
		{
			cout << "Support GoToSafePlace" << endl;
			pn->setCurrentState(new GoToSafePlace());
			pn->getCurrentState()->onEnter(pn);
		}
	}
}

void GoToStorage::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setIsMoving(true);
	}
}

void GoToStorage::onExit(NPC* pn)
{
}
