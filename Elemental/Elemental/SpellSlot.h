#pragma once
#include <SFML/Graphics.hpp>
#include "Spell.h"
#include "FireSpells.h"
using namespace sf;
using namespace std;


class SpellSlot
{
public:
	SpellSlot(vector<Spell*>* activeSpells);
	~SpellSlot();
	void SetSpell(SPELL s);
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	Sprite icon;
protected:
	SPELL spell;
	Texture tex;
	vector<Spell*>* active;
};

