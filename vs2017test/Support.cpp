#include "Support.h"
#include "Team.h"

Support::Support()
{
}

Support::Support(const Point& position, Soldier** soldiers, int teamId, int** maze, double** securityMap) : NPC(position, teamId, maze, securityMap)
{
	this->soldiers = soldiers;
	this->closestHealthStorage = nullptr;
	this->closestAmmoStorage = nullptr;
	this->health = 0;
	this->ammo = 0;
	this->pCurrentState = new GoToStorage();
	this->pCurrentState->onEnter(this);
}

Support::~Support()
{
	if (this->closestHealthStorage != nullptr) {
		delete this->closestHealthStorage;
	}
	if (this->closestAmmoStorage != nullptr) {
		delete this->closestAmmoStorage;
	}
}

void Support::show()
{
}

void Support::goToSafePlace()
{
	if (this->moveToSafestPosition())
	{
		for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
		{
			if (this->soldiers[i]->isWaitingForSupport())
			{
				this->setCurrentState(new SupplyToSoldier());
				this->pCurrentState->onEnter(this);
			}
		}
	}
}

void Support::setClosestHealthStorage(HealthStorage* closestHealthStorage)
{
	this->closestHealthStorage = closestHealthStorage;
}

void Support::setClosestAmmoStorage(AmmoStorage* closestAmmoStorage)
{
	this->closestAmmoStorage = closestAmmoStorage;
}

void Support::bringHealthToSoldiers()
{
	for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
	{
		if (this->soldiers[i]->hpLack() > 0)
		{
			this->setTarget(this->soldiers[i]->getPosition());
			return;
		}
	}
}

void Support::takeHealthFromStorage()
{
	this->health += this->closestHealthStorage->supply(MAX_HEALTH - this->health);
}

void Support::takeAmmoFromStorage()
{
	this->ammo += this->closestAmmoStorage->supply(MAX_AMMO - ammo);
}

void Support::goToClosestHealthStorage()
{
	if (this->closestHealthStorage != nullptr)
	{
		this->setTarget(this->closestHealthStorage->getPosition());
	}
}

void Support::goToClosestAmmoStorage()
{
	if (this->closestAmmoStorage != nullptr)
	{
		this->setTarget(this->closestAmmoStorage->getPosition());
	}
}

void Support::supplyToSoldier()
{
	for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
	{
		if (this->soldiers[i]->isWaitingForSupport())
		{
			if (this->health > 25 && this->soldiers[i]->getHP() < 50)
			{
				if (this->target == this->soldiers[i]->getPosition())
				{
					this->soldiers[i]->supplyHP(this->health); // change health
				}
				this->setTarget(this->soldiers[i]->getPosition());
			}
			else if (this->ammo > 40 && this->soldiers[i]->getLoadedBullets() < 60)
			{
				if (this->target == this->soldiers[i]->getPosition())
				{
					this->soldiers[i]->supplyBullets(this->ammo); // change ammo
				}
				this->setTarget(this->soldiers[i]->getPosition());
			}
			else
			{
				this->setCurrentState(new GoToStorage());
				this->pCurrentState->onEnter(this);
			}
		}
	}
}
