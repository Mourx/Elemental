#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Spell.h"
#include "FireSpells.h"
#include "WaterSpells.h"
#include "AirSpells.h"
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
	void NextElementLeft();
	void NextElementRight();
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
	vector<ELEMENT> currentElements;
	map<ELEMENT, vector<SPELL>* > spellTable;
	
	vector<ELEMENT> elementOrder;
	float leftElementIndex = 0;
	float rightElementIndex = 1;

	Sprite SpellBackLayerLeft;
	Sprite SpellBackLayerRight;
	Texture leftBackTex;
	Texture rightBackTex;

	bool bSwitchedSpellLeft = false;
	bool bSwitchedSpellRight = false;
	float spellSwitchCooldown = 0.3;
	float spellSwitchTimerLeft = 0;
	float spellSwitchTimerRight = 0;

	bool bSwitchedElementLeft = false;
	bool bSwitchedElementRight = false;
	float elementSwitchCooldown = 2;
	float elementSwitchTimerLeft = 0;
	float elementSwitchTimerRight = 0;

};

