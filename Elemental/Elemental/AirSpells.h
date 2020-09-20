#pragma once
#include "Spell.h"

class LightningStrike : public Spell
{
public:
	LightningStrike();
	~LightningStrike();
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	void EffectUpdate(Time t);
	SpellEffect* Collide();
};