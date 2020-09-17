#pragma once
#include "SFML//Graphics.hpp"
#include "Enemy.h"
#include "enums.h"
using namespace sf;
using namespace std;

class SpellEffect
{
public:
	SpellEffect();
	~SpellEffect();
	virtual void Draw(RenderWindow* window);
	virtual void Update(Time t);
	void AddEnemy(Enemy* e) { affectedEnemies.push_back(e); }
	bool IsFinished() { return bEffect; }
	Sprite icon;
protected:
	Texture tex;
	Shader effectShade;
	float scale = 1;
	float damage = 0;
	vector<Enemy*> affectedEnemies;
	float effectDuration = 300000;
	float effectTimer = 0;
	bool bEffect = true;
};

class BaseCircle : public SpellEffect
{
public:
	BaseCircle(Vector2f pos, float dmg, ELEMENT type);
	~BaseCircle();

	void Update(Time t);

};