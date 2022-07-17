#include "Bullet.h"

Bullet::Bullet()
{
}

// angle must be in radians
Bullet::Bullet(double x, double y, const Point& shootingPosition, double directionAngle) : Ammo(x, y)
{
	this->shootingPosition = shootingPosition;
	this->directionAngle = directionAngle;
	this->isMoving = false;
}

Bullet::~Bullet()
{
}

void Bullet::show()
{
	if (this->isMoving)
	{
		glColor3d(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2d(this->x - 0.5, this->y);
		glVertex2d(this->x, this->y + 0.5);
		glVertex2d(this->x + 0.5, this->y);
		glVertex2d(this->x, this->y - 0.5);
		glEnd();
	}
}

Point* Bullet::move(int** maze)
{
	Point* point = nullptr;
	double dx, dy;

	if (this->isMoving)
	{
		dx = cos(this->directionAngle);
		dy = sin(this->directionAngle);
		this->x += dx * SPEED;
		this->y += dy * SPEED;
		if (maze[(int)this->y][(int)this->x] != SPACE)
		{
			this->isMoving = false;
			point = new Point((int)this->y, (int)this->x);
		}
	}
	return point;
}

void Bullet::simulateMotion(int** maze, double** securityMap, double damage)
{
	double dx, dy;
	dx = cos(this->directionAngle);
	dy = sin(this->directionAngle);

	while (this->isMoving)
	{
		this->x += dx * SPEED;
		this->y += dy * SPEED;

		securityMap[(int)this->y][(int)this->x] += damage; // drawing in map

		if (maze[(int)y][(int)x] != SPACE)
			this->isMoving = false;
	}
}

void Bullet::simulateVisibility(int** maze, double** visibilityMap)
{
	double dx, dy;
	dx = cos(directionAngle);
	dy = sin(directionAngle);

	while (this->isMoving)
	{
		this->x += dx * SPEED;
		this->y += dy * SPEED;

		visibilityMap[(int)y][(int)x] = 1; // drawing in map

		if (maze[(int)y][(int)x] != SPACE)
			this->isMoving = false;
	}
}
