#pragma once
#include <math.h>
#include "glut.h"
#include "Definitions.h"
#include "Ammo.h"

class Bullet : public Ammo
{

private:
	static constexpr float SPEED = 0.1f;
	double directionAngle;
	bool isMoving;

public:
	Bullet();
	Bullet(double x, double y, double directionAngle);
	~Bullet();

	void show();
	void fire() { isMoving = true; }
	void move(int** maze);
	bool getIsMoving() { return isMoving; }
	void simulateMotion(int** maze, double** securityMap, double damage);
	void simulateVisibility(int** maze, double** securityMap);
};
