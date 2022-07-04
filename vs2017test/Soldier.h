#pragma once
#include "NPC.h"
#include "Bullet.h"
#include "Grenade.h"

class Soldier : public NPC
{
public:
	static constexpr int MAX_BULLETS = 30;
	static constexpr int MAX_GRENADES = 3;
private:
	Bullet* pBullet;
	Grenade* pGrenade;
	int numOfBullets, numOfGrenades;

public:
	Soldier();
	Soldier(Point position);
	~Soldier();

	int getNumOfBullets() { return this->numOfBullets; }
	int getNumOfGrenades() { return this->numOfGrenades; }
	void play(int** maze, double** securityMap);
	void show();
	void shoot(int** maze);
	void throwGrenade(int** maze);
};
