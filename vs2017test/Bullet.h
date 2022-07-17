#pragma once
#include <math.h>
#include "glut.h"
#include "Definitions.h"
#include "Ammo.h"

class Bullet : public Ammo
{
private:
	static constexpr float SPEED = 0.1f;
	Point shootingPosition;
	double directionAngle;
	bool isMoving;

public:
	Bullet();
	Bullet(double x, double y, const Point& shootingPosition, double directionAngle);
	~Bullet();

	Point getShootingPosition() const { return this->shootingPosition; }
	void show();
	void fire() { isMoving = true; }
	Point* move(int** maze);
	bool getIsMoving() { return isMoving; }
	void simulateMotion(int** maze, double** securityMap, double damage);
	void simulateVisibility(int** maze, double** securityMap);
};
