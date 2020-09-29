#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "EnemyAttack.h"
class Player;
using namespace sf;
using namespace std;
class EnemyAttack;
class Enemy
{
public:
	Enemy();
	~Enemy();
	Sprite icon;
	void Draw(RenderWindow* window);
	void Damage(float dmg, ELEMENT spellType);
	void Update(Time t);
	virtual void Attack(Player* player) {};
	
	bool IsDead() { return bDead; }
protected:
	virtual void Move();
	Texture tex;
	float health = 0;
	float damage = 0;
	ELEMENT element = FIRE;
	bool bDead = false;
	bool bDamageFlash = false;
	float flashTimer = 0.f;
	float flashDuration = 0.2f;
	Shader damageShade;

	float attackRate = 1.f;
	float attackTimer = 0;
	bool bCanAttack = false;

	Player* player;
	vector<EnemyAttack*>* attacks;

	bool bCanMove = false;
	float moveTimer = 0.f;
	float moveDelay = 2.f;
	float HSpeed = 3;
	float VSpeed = 3;
};

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy();
};