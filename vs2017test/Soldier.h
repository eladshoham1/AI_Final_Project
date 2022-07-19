#pragma once
#include "NPC.h"
#include "Bullet.h"
#include "Grenade.h"
#include "SearchEnemy.h"
#include "ReloadBullets.h"

class Soldier : public NPC
{
public:
	static constexpr int MAX_BULLETS = 100;

private:
	Bullet* pBullet;
	Grenade* pGrenade;
	int loadedBullets;
	int bulletsInStock;
	bool supporterAlive;
	bool waitingForSupport;
	
public:
	Soldier();
	Soldier(const Point& position, int teamId, int** maze, double** securityMap);
	~Soldier();

	Bullet* getPBullet() { return this->pBullet; }
	Grenade* getPGrenade() { return this->pGrenade; }
	int getLoadedBullets() { return this->loadedBullets; }
	int getBulletsInStock() { return this->bulletsInStock; }
	bool hasSupporterAlive() { return this->supporterAlive; }
	void setSupporterAlive(bool supporterAlive) { this->supporterAlive = supporterAlive; }
	bool hasLoadedBullets() { return this->loadedBullets > 0; }
	bool hasBulletsInStock() { return this->bulletsInStock > 0; }
	bool isWaitingForSupport() { return this->waitingForSupport; }
	void setWaitingForSupport(bool waitingForSupport) { this->waitingForSupport = waitingForSupport; }
	int ammoLack() { return MAX_BULLETS - this->bulletsInStock; }
	bool needToReloadBullets() { return this->loadedBullets == 0; }
	void supplyBullets(int bullets);
	void setVisibilityMap();
	void loadBullets();
	void addBulletsToStock(int numOfBullets);
	bool isEnemyVisible();
	void attack();
	bool shoot();
	bool throwGrenade();
	void goToSafePlace();
	void show();
};
