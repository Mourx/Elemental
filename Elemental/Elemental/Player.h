#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Spell.h"
#include "FireSpells.h"
#include "WaterSpells.h"
#include "SpellSlot.h"
#include "SpellEffect.h"
using namespace sf;
using namespace std;
class Player
{
public:
	Player(TileMap* c);
	~Player();
	void Update(Time t);
	void SetPosition(Vector2f p);
	void MousePressed(Vector2i pos);
	void Draw(RenderWindow* window);
	Vector2f GetPosition() { return position; };
	Sprite icon;
private:
	Texture tex;
	TileMap* currentMap;
	void CheckKeys(Time t);
	void CheckMove(Vector2f pos);
	void UpdateCollisions();
	Vector2f position;
	float HSpeed = 45;
	float VSpeed = 45;
	int spellIndexLeft = 0;
	int spellIndexRight = 0;
	SpellSlot* leftSpell;
	SpellSlot* rightSpell;
	vector<Spell*> spellList;
	vector<Spell*>* activeSpells = new vector<Spell*>(0);
	vector<SpellEffect*> activeEffects;
	map<ELEMENT, vector<SPELL>* > spellTable;
};

