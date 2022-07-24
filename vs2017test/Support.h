#pragma once
#include <math.h>
#include "NPC.h"
#include "Soldier.h"
#include "Cell.h"
#include "HealthStorage.h"
#include "AmmoStorage.h"
#include "GoToStorage.h"

class Support : public NPC
{
private:
	static constexpr int MAX_HEALTH = 150;
	static constexpr int MAX_AMMO = 300;
	static constexpr int MIN_AMOUNT_TO_SUPPLY = 25;
	Soldier** soldiers;
	HealthStorage* closestHealthStorage;
	AmmoStorage* closestAmmoStorage;
	int health;
	int ammo;

public:
	Support();
	Support(const Point& position, Soldier** soldiers, int teamId, int** maze, double** securityMap);
	~Support();

	Soldier** getSoldiers() { return this->soldiers; }
	HealthStorage* getClosestHealthStorage() { return this->closestHealthStorage; }
	AmmoStorage* getClosestAmmoStorage() { return this->closestAmmoStorage; }
	void setClosestHealthStorage(HealthStorage* closestHealthStorage);
	void setClosestAmmoStorage(AmmoStorage* closestAmmoStorage);
	int getHealth() const { return this->health; }
	int getAmmo() const { return this->ammo; }
	void takeHealth();
	void setRandomBehavior();
	void bringHealthToSoldiers();
	void takeSupplyFromStorage();
	void goToClosestHealthStorage();
	void goToClosestAmmoStorage();
	void supplyToSoldierFromStorage(Soldier* soldier);
	void supplyHealthToSoldier(Soldier* soldier);
	void supplyAmmoToSoldier(Soldier* soldier);
	void supplyToSoldier();
	void show();
};

