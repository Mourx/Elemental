#include "SpellSlot.h"


SpellSlot::SpellSlot(vector<Spell*>* activeSpells) {
	active = activeSpells;
}

SpellSlot::~SpellSlot() {

}

void SpellSlot::SetSpell(SPELL s) {
	spell = s;
}

void SpellSlot::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {
	Spell* instance = new Spell();
	switch (spell) {
	case FIREBOLT:
		instance = new FireBolt();
		break;
	default:
		break;
	}
	instance->Fire(target, origin, enemy);
	active->push_back(instance);
}