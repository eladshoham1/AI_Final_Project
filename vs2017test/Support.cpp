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
	this->setRandomBehavior();
}

Support::~Support()
{
	if (this->closestHealthStorage != nullptr)
		delete this->closestHealthStorage;
	if (this->closestAmmoStorage != nullptr)
		delete this->closestAmmoStorage;
}

void Support::show()
{
}

void Support::setClosestHealthStorage(HealthStorage* closestHealthStorage)
{
	this->closestHealthStorage = closestHealthStorage;
}

void Support::setClosestAmmoStorage(AmmoStorage* closestAmmoStorage)
{
	this->closestAmmoStorage = closestAmmoStorage;
}

void Support::takeHealth()
{
	this->supplyHP(this->health);
}

void Support::setRandomBehavior()
{
	int choose = rand() % NUM_OF_STATES;
	switch (choose)
	{
	case 0:
		this->setCurrentState(new GoToSafePlace());
		break;
	case 1:
		this->setCurrentState(new GoToStorage());
		break;
	case 2:
		this->setCurrentState(new SupplyToSoldier());
		break;
	}
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

void Support::takeSupplyFromStorage()
{
	if (this->closestHealthStorage != nullptr)
	{
		if (this->target == this->closestHealthStorage->getPosition())
			this->health += this->closestHealthStorage->supply(MAX_HEALTH - this->health);
	}
	else if (this->closestAmmoStorage != nullptr)
	{
		if (this->target == this->closestAmmoStorage->getPosition())
			this->ammo += this->closestAmmoStorage->supply(MAX_AMMO - this->ammo);
	}
}

void Support::goToClosestHealthStorage()
{
	if (this->closestHealthStorage != nullptr)
		this->setTarget(this->closestHealthStorage->getPosition());
}

void Support::goToClosestAmmoStorage()
{
	if (this->closestAmmoStorage != nullptr)
		this->setTarget(this->closestAmmoStorage->getPosition());
}

void Support::supplyToSoldierFromStorage(Soldier* soldier)
{
	this->supplyHealthToSoldier(soldier);
	this->supplyAmmoToSoldier(soldier);
}

void Support::supplyHealthToSoldier(Soldier* soldier)
{
	double amount = soldier->hpLack();
	this->health -= soldier->supplyHP(this->health > amount ? amount : this->health);
}

void Support::supplyAmmoToSoldier(Soldier* soldier)
{
	int amount = soldier->ammoLack();
	if (this->ammo > amount)
	{
		soldier->supplyBullets(amount);
		this->ammo -= amount;
	}
	else
	{
		soldier->supplyBullets(this->ammo);
		this->ammo = 0;
	}
}

void Support::supplyToSoldier()
{
	Soldier* soldier = nullptr;
	double minValue = this->soldiers[0]->hpLack();
	bool isSoldierNeedHealth = true;

	for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
	{
		if (!this->soldiers[i]->isDead())
		{
			if (this->soldiers[i]->hpLastThanHalf())
			{
				if (soldier == nullptr || this->soldiers[i]->hpLack() < minValue)
				{
					soldier = this->soldiers[i];
					minValue = this->soldiers[i]->hpLack();
					isSoldierNeedHealth = true;
				}
			}
			if (this->soldiers[i]->ammoLastThanHalf())
			{
				if (soldier == nullptr || this->soldiers[i]->ammoLack() < minValue)
				{
					soldier = this->soldiers[i];
					minValue = this->soldiers[i]->ammoLack();
					isSoldierNeedHealth = false;
				}
			}
		}
	}

	if (soldier)
	{
		if (abs(this->position.getX() - soldier->getPosition().getX()) <= 1 && abs(this->position.getY() - soldier->getPosition().getY()) <= 1)
			this->supplyToSoldierFromStorage(soldier);
		else if ((isSoldierNeedHealth && this->health >= MIN_AMOUNT_TO_SUPPLY) || (!isSoldierNeedHealth && this->ammo >= MIN_AMOUNT_TO_SUPPLY))
			this->setTarget(soldier->getPosition());
		else
			this->setCurrentState(new GoToStorage());
	}
	else if (this->health < MIN_AMOUNT_TO_SUPPLY || this->ammo < MIN_AMOUNT_TO_SUPPLY)
		this->setCurrentState(new GoToStorage());
}
