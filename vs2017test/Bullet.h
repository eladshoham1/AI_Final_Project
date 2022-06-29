#pragma once
#include "Definitions.h"
const double SPEED = 0.1;

class Bullet
{

private:
	double x, y;
	double directionAngle;
	bool isMoving;
public:
	Bullet();
	Bullet(double x, double y, double angle);
	~Bullet();

	void show();
	void fire() { isMoving = true; }
	void move(int** maze);
	bool getIsMoving() { return isMoving; }
	void simulateMotion(int** maze, double** securityMap, double damage);
	void simulateVisibility(int** maze, double** securityMap);
};
