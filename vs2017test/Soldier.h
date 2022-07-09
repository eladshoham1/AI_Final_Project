#pragma once
#include "NPC.h"
#include "Bullet.h"
#include "Grenade.h"
#include "SearchEnemy.h"

class Soldier : public NPC
{
public:
	static constexpr int MAX_BULLETS = 100;

private:
	Bullet* pBullet;
	Grenade* pGrenade;
	int loadedBullets;
	int bulletsInStock;
	bool waitingForSupport;
	
public:
	Soldier();
	Soldier(const Point& position, int teamId, int** maze, double** securityMap);
	~Soldier();

	int getLoadedBullets() { return this->loadedBullets; }
	int getBulletsInStock() { return this->bulletsInStock; }
	bool hasLoadedBullets() { return this->loadedBullets > 0; }
	bool hasBulletsInStock() { return this->bulletsInStock > 0; }
	bool isWaitingForSupport() { return this->waitingForSupport; }
	void setWaitingForSupport(bool waitingForSupport) { this->waitingForSupport = waitingForSupport; }
	void setVisibilityMap();
	void loadBullets();
	void addBulletsToStock(int numOfBullets);
	double distanceFromEnemy();
	bool isEnemyVisible();
	void attack();
	bool shoot();
	bool throwGrenade();
	void show();
};
