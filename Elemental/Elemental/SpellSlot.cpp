#include "SpellSlot.h"


SpellSlot::SpellSlot(vector<Spell*>* activeSpells,vector<SPELL>* list) {
	active = activeSpells;

	texBackground.loadFromFile("Textures/Spells/SpellSlots/SpellSlot_Background.png");
	texCooldown.loadFromFile("Textures/Spells/SpellSlots/SpellSlot_Cooldown.png");

	cooldownShader.loadFromFile("Textures/Shaders/effectCooldown.vert", Shader::Vertex);
	spellList = spellList;
	icon.setTexture(texBackground);
	cooldownIcon.setTexture(texCooldown);
	//cooldownIcon.setOrigin(0, 32);
}

SpellSlot::~SpellSlot() {

}

void SpellSlot::SetSpell(SPELL s) {
	spell = s;
	Spell* instance = new Spell();
	switch (spell) {
	case FIREBOLT:
		instance = new FireBolt();
		break;
	case WATERBALL:
		instance = new WaterBall();
		break;
	default:
		break;
	}
	currentSpell = instance;
	spellIcon = currentSpell->icon;
	
}


void SpellSlot::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {
	
	currentSpell->Fire(target, origin, enemy);
	active->push_back(currentSpell);
	bReady = false;
}

void SpellSlot::Draw(RenderWindow* window) {
	window->draw(icon);
	window->draw(spellIcon);
	window->draw(cooldownIcon, &cooldownShader);
	
	for (Spell* spell : *active) {
		window->draw(spell->icon);
	}
}

void SpellSlot::Update(Time t) {
	for (Spell* spell : *active) {
		spell->Update(t);
	}
	if (bReady == false) {
		float time = t.asSeconds();
		cooldownTimer += time;
		float percentage = (currentSpell->GetCooldown() - cooldownTimer) / currentSpell->GetCooldown();
		cooldownIcon.setScale(1, percentage); 
		if (cooldownTimer >= currentSpell->GetCooldown()) {
			bReady = true;
			cooldownTimer = 0;
		}
	}
}

void SpellSlot::SetPosition(Vector2f pos) {
	icon.setPosition(pos);
	cooldownIcon.setPosition(pos );
	spellIcon.setPosition(pos + Vector2f(8, 8));
}