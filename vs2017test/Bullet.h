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
	Bullet(const Point& shootingPosition, double x, double y, double directionAngle);
	~Bullet();

	Point getShootingPosition() const { return this->shootingPosition; }
	void setShootingPosition(const Point& shootingPosition) { this->shootingPosition = shootingPosition; }
	void show();
	void fire() { isMoving = true; }
	Point* move(int** maze);
	bool getIsMoving() { return isMoving; }
	void simulateMotion(int** maze, double** securityMap, double damage);
	void simulateVisibility(int** maze, double** securityMap);
};
