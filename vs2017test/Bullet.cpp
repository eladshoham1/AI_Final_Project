#include <math.h>
#include "glut.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

// angle must be in radians
Bullet::Bullet(double x, double y, double angle)
{
	this->x = x;
	this->y = y;
	this->directionAngle = angle;
	this->isMoving = false;
}

Bullet::~Bullet()
{
}

void Bullet::show()
{
	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x, y + 0.5);
	glVertex2d(x + 0.5, y);
	glVertex2d(x, y - 0.5);
	glEnd();
}

void Bullet::move(int** maze)
{
	double dx, dy;
	if (isMoving)
	{
		dx = cos(this->directionAngle);
		dy = sin(this->directionAngle);
		x += dx * SPEED;
		y += dy * SPEED;
		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}
}

void Bullet::simulateMotion(int** maze, double** securityMap, double damage)
{
	double dx, dy;
	dx = cos(directionAngle);
	dy = sin(directionAngle);
	while (isMoving)
	{
		x += dx * SPEED;
		y += dy * SPEED;

		securityMap[(int)y][(int)x] += damage; // drawing in map

		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}
}

void Bullet::simulateVisibility(int** maze, double** visibilityMap)
{
	double dx, dy;
	dx = cos(directionAngle);
	dy = sin(directionAngle);
	while (isMoving)
	{
		x += dx * SPEED;
		y += dy * SPEED;

		visibilityMap[(int)y][(int)x] = 1; // drawing in map

		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}
}
