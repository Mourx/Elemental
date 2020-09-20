#pragma once
#include <SFML/Graphics.hpp>
#include "Spell.h"
#include "FireSpells.h"
#include "WaterSpells.h"
using namespace sf;
using namespace std;


class SpellSlot
{
public:
	SpellSlot(vector<Spell*>* activeSpells,vector<SPELL>* list);
	~SpellSlot();
	void SetSpell(SPELL s);
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	void Draw(RenderWindow* window);
	void Update(Time t);
	void SetPosition(Vector2f pos);
	bool IsReady() { return bReady; }
	Sprite icon;
protected:
	bool bReady = true;
	SPELL spell;
	Sprite spellIcon;
	Sprite cooldownIcon;
	Spell* currentSpell;
	Texture texBackground;
	Texture texCooldown;
	Shader cooldownShader;
	float cooldown;
	float cooldownTimer;
	vector<Spell*>* active;
	vector<SPELL>* spellList;
};

