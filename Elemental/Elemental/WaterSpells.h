#pragma once
#include "Spell.h"
class WaterBall : public Spell {
public:
	WaterBall();
	~WaterBall();
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	void EffectUpdate(Time t);
	SpellEffect* Collide();

};

class WaterPulse : public Spell {
public:
	WaterPulse();
	~WaterPulse();
	void Fire(Vector2f target, Vector2f origin, Enemy* enemy);
	void EffectUpdate(Time t);
	SpellEffect* Collide();

};