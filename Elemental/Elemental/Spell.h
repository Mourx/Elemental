#pragma once
#include "enums.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "SpellEffect.h"
using namespace sf;
using namespace std;
class Spell
{
public:
	Spell();
	~Spell();
	virtual void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	virtual void Update(Time t);
	virtual void Draw(RenderWindow* window);
	virtual SpellEffect* Collide();
	bool IsFinished() { return bIsFinished; }
	bool HasCollided() { return bCollided; }
	Sprite icon;
protected:
	virtual void EffectUpdate(Time t);
	Texture tex;
	ELEMENT element;
	float damage;
	float speed;
	float hDirection;
	float vDirection;
	Vector2f targetPoint;
	Enemy* targetEnemy;
	TARGET_TYPE targetType;
	bool bReachedTarget;
	bool bIsFinished;
	float effectDuration = 200000;
	float effectTimer = 0;
	bool bEffect = false;
	bool bCollided = false;
	Shader effectShade;
};
