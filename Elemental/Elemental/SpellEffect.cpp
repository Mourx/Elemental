#include "SpellEffect.h"

SpellEffect::SpellEffect() {

}


SpellEffect::~SpellEffect() {

}

void SpellEffect::Draw(RenderWindow* window) {
	window->draw(icon, &effectShade);
}

void SpellEffect::Update(Time t) {
	
}

void SpellEffect::AddEnemy(Enemy* e) {
	bool bContains = false;
	for (Enemy* ene : affectedEnemies) {
		if (ene == e) {
			bContains = true;
		}
	}
	if (!bContains) {
		e->Damage(damage);
		affectedEnemies.push_back(e);
	}
}