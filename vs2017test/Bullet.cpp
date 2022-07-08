#include "Bullet.h"

Bullet::Bullet()
{
}

// angle must be in radians
Bullet::Bullet(Point position, double directionAngle) : Ammo(position)
{
	this->directionAngle = directionAngle;
	this->isMoving = false;
}

Bullet::~Bullet()
{
}

void Bullet::show()
{
	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2d(this->position.getX() - 0.5, this->position.getY());
	glVertex2d(this->position.getX(), this->position.getY() + 0.5);
	glVertex2d(this->position.getX() + 0.5, this->position.getY());
	glVertex2d(this->position.getX(), this->position.getY() - 0.5);
	glEnd();
}

void Bullet::move(int** maze)
{
	double dx, dy;

	if (this->isMoving)
	{
		dx = cos(this->directionAngle);
		dy = sin(this->directionAngle);

		this->position.setX((int)(this->position.getX() + dx * SPEED));
		this->position.setY((int)(this->position.getX() + dy * SPEED));
		if (maze[this->position.getY()][this->position.getX()] != SPACE)
			isMoving = false;
	}
}

void Bullet::simulateMotion(int** maze, double** securityMap, double damage)
{
	double dx, dy;
	dx = cos(this->directionAngle);
	dy = sin(this->directionAngle);

	while (this->isMoving)
	{
		this->position.setX((int)(this->position.getX() + dx * SPEED));
		this->position.setY((int)(this->position.getX() + dy * SPEED));

		securityMap[this->position.getY()][this->position.getX()] += damage; // drawing in map

		if (maze[this->position.getY()][this->position.getX()] != SPACE)
			isMoving = false;
	}
}

void Bullet::simulateVisibility(int** maze, double** visibilityMap)
{
	double dx, dy;
	dx = cos(directionAngle);
	dy = sin(directionAngle);

	while (this->isMoving)
	{
		this->position.setX((int)(this->position.getX() + dx * SPEED));
		this->position.setY((int)(this->position.getX() + dy * SPEED));

		visibilityMap[this->position.getY()][this->position.getX()] = 1; // drawing in map

		if (maze[this->position.getY()][this->position.getX()] != SPACE)
			isMoving = false;
	}
}
