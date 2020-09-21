#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"
#include "SpellEffect.h"
using namespace sf;
class SpellEffect;
class EnemyAttack
{
public:
	EnemyAttack();
	~EnemyAttack();
	virtual void Update(Time t);
	void Draw(RenderWindow* window);
	virtual SpellEffect* Collide();
	bool HasCollided() { return bCollided; }
	bool IsFinished() { return bIsFinished; }
	bool ReachedTarget() { return bReachedTarget; }
	Sprite icon;

protected:
	Vector2f position;
	Vector2f targetPoint;
	float hDirection;
	float vDirection;
	float speed;
	bool bReachedTarget = false;
	bool bCollided = false;
	bool bIsFinished = false;
	float effectDuration = 0.5;
	float effectTimer = 0;
	bool bEffect = false;
	ELEMENT ele;
	float damage;
	Texture tex;
	Shader effectShade;
};

class EnemyProjectile : public EnemyAttack
{
public: 
	EnemyProjectile(Vector2f target ,Vector2f origin,float dmg,ELEMENT ele);
	~EnemyProjectile();
	void Update(Time t);
	SpellEffect* Collide();
};


class EnemyMelee : public EnemyAttack
{
public:
	EnemyMelee();
	~EnemyMelee();
};