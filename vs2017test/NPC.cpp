#include "NPC.h"

NPC::NPC()
{
}

NPC::NPC(Point position)
{
	this->position = position;
	this->pCurrentState = nullptr;
	this->isMoving = false;
	this->hp = MAX_HP;
}

NPC::~NPC()
{
}

/*void NPC::play()
{
	if (atHome)
	{
		hp += 0.5;
		// check if the NPC should do something else
		if (hp >= MAX_HP)
			pCurrentState->Transform(this);
	}
	else // not at home
	{
		hp -= 0.2;
		// check if the NPC should do something else
		if (hp <= MAX_HP * 0.2 && !goingHome) // 20% of full HP
			pCurrentState->Transform(this);

	}

	if (isMoving)
	{
		x += dx * SPEED;
		y += dy * SPEED;
		// check if the NPC should do something else
		if (fabs(x - targetX) < 1 && fabs(y - targetY) < 1)
			pCurrentState->Transform(this);
	}
	else if (!atHome)// not moving
	{
		if (isGettingWood)
		{
			numWood++;
			// check if the NPC should do something else
			if (numWood >= MAX_WOOD)
				pCurrentState->Transform(this);
		}
		else
		{
			numWood--;
			// check if the NPC should do something else
			if (numWood <= MIN_WOOD)
				pCurrentState->Transform(this);
		}
	}
}*/

/*void NPC::setDestination(Point target)
{
	double distance;
	this->target = target;
	distance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
	// [dx,dy] must be vector of length 1 to the direction to target
	dx = (targetX - x) / distance;
	dy = (targetY - y) / distance;

}*/
