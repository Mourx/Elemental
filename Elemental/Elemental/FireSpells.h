#pragma once;
#include "Spell.h"

class FireBolt : public Spell {
public:
	FireBolt();
	~FireBolt();
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	void EffectUpdate(Time t);
	SpellEffect* Collide();
};