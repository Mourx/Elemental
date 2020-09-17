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