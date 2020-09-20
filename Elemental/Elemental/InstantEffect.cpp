#include "SpellEffect.h"


InstantEffect::InstantEffect(Enemy* e, float dmg, ELEMENT type, EFFECT_TYPE effType, float size) {
	damage = dmg;
	e->Damage(damage);
}

InstantEffect::~InstantEffect() {

}

void InstantEffect::Update(Time t) {

}