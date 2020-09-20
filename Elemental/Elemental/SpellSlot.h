#pragma once
#include <SFML/Graphics.hpp>
#include "Spell.h"
#include "FireSpells.h"
#include "WaterSpells.h"
#include "AirSpells.h"
using namespace sf;
using namespace std;


class SpellSlot
{
public:
	SpellSlot(vector<Spell*>* activeSpells,vector<SPELL>* list, ELEMENT e);
	~SpellSlot();
	Spell* SetSpell(SPELL s, Spell* spell);
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	void Draw(RenderWindow* window);
	void Update(Time t);
	void SetPosition(Vector2f pos);
	void SetSpellList(vector<SPELL>* list, ELEMENT e);
	void UpdateSpells();
	void NextSpell();
	TARGET_TYPE GetTargetType() { return currentSpell->GetType(); }
	ELEMENT GetElement() { return currentElement; }
	bool IsReady() { return bReady; }
	Sprite currentBackground;
protected:
	bool bReady = true;
	SPELL spell;
	Sprite spellIcon;
	Sprite cooldownIcon;
	Spell* currentSpell;
	Texture texBackground;
	Texture texCooldown;
	Shader cooldownShader;
	float spellIndex;
	float cooldown;
	float cooldownTimer;
	vector<Spell*>* active;
	vector<SPELL>* spellList;
	ELEMENT currentElement;
	Sprite prevSpellIcon;
	Sprite nextSpellIcon;
	Sprite prevBackground;
	Sprite nextBackground;
	Spell* prevSpell;
	Spell* nextSpell;
	Shader notCurrent;


	Texture elementIcon;
	Sprite currentEleIcon;
	Sprite prevElement;
	Sprite nextElement;

};

