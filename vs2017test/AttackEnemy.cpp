#include "AttackEnemy.h"
#include "Soldier.h"

AttackEnemy::AttackEnemy()
{
}

AttackEnemy::~AttackEnemy()
{
}

void AttackEnemy::transform(NPC* pn)
{
}

void AttackEnemy::onEnter(NPC* pn)
{
	/*Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
		soldier->setIsAttacking(true);*/
}

void AttackEnemy::onExit(NPC* pn)
{
}
