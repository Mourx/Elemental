#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"
using namespace sf;
using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	Sprite icon;
	void Draw(RenderWindow* window);
	void Damage(float dmg);
	void Update(Time t);
	bool IsDead() { return bDead; }
protected:
	Texture tex;
	float health;
	ELEMENT element;
	bool bDead;
	bool bDamageFlash = false;
	float flashTimer = 0;
	float flashDuration = 0.2;
	Shader damageShade;
};

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy();
};