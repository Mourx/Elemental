#pragma once
#include "Enemy.h"
#include "Player.h"
#include "EnemyAttack.h"
class Slime : public Enemy
{
public:
	Slime(vector<EnemyAttack*>* attacks, Player* p);
	~Slime();
	void Attack(Player* player);
};