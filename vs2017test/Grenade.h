#pragma once
#include "Bullet.h"

const int NUM_BULLETS = 100;

class Grenade
{

private:
	double x, y;
	Bullet* bullets[NUM_BULLETS];
	bool isExploded;
public:
	Grenade();
	Grenade(double x, double y);
	~Grenade();

	bool getIsExploded() { return this->isExploded; }
	void explode();
	void exploding(int** maze);
	void show();
	void simulateExplosion(int** maze, double** securityMap, double damage);
	void simulateVisibility(int** maze, double** visibilityMap);
};
