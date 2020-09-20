#include "SpellSlot.h"


SpellSlot::SpellSlot(vector<Spell*>* activeSpells,vector<SPELL>* list, ELEMENT e) {
	active = activeSpells;
	currentElement = e;
	spellList = list;
	texBackground.loadFromFile("Textures/Spells/SpellSlots/SpellSlot_Background.png");
	texCooldown.loadFromFile("Textures/Spells/SpellSlots/SpellSlot_Cooldown.png");

	cooldownShader.loadFromFile("Textures/Shaders/effectCooldown.vert", Shader::Vertex);
	notCurrent.loadFromFile("Textures/Shaders/unavailable.vert", Shader::Vertex);
	currentBackground.setTexture(texBackground);
	prevBackground.setTexture(texBackground);
	nextBackground.setTexture(texBackground);

	cooldownIcon.setTexture(texCooldown);
	cooldownIcon.setScale(1, 0);
	spellIndex = 0;

	currentEleIcon.setOrigin(4, 4);
	elementIcon.loadFromFile("Textures/Spells/Fire/Fire.png");
	UpdateSpells();
}

SpellSlot::~SpellSlot() {

}

Spell* SpellSlot::SetSpell(SPELL s,Spell* sp) {
	sp = new Spell();
	switch (s) {
	case FIREBOLT:
		sp = new FireBolt();
		break;
	case WATERBALL:
		sp = new WaterBall();
		break;
	case WATERPULSE:
		sp = new WaterPulse();
		break;
	case LIGHTNINGSTRIKE:
		sp = new LightningStrike();
		break;
	default:
		break;
	}
	return sp;
}

void SpellSlot::NextSpell() {
	spellIndex++;
	if (spellIndex >= spellList->size()) {
		spellIndex = 0;
	}
	UpdateSpells();
}

void SpellSlot::UpdateSpells() {
	currentSpell = SetSpell((*spellList)[spellIndex], currentSpell);
	spellIcon = currentSpell->icon;

	switch (currentElement) {
	case FIRE:
		elementIcon.loadFromFile("Textures/Spells/Fire/Fire.png");
		break;
	case WATER:
		elementIcon.loadFromFile("Textures/Spells/Water/Water.png");
		break;
	case EARTH:
		elementIcon.loadFromFile("Textures/Spells/Earth/Earth.png");
		break;
	case AIR:
		elementIcon.loadFromFile("Textures/Spells/Air/Air.png");
		break;
	case BLOOD:
		elementIcon.loadFromFile("Textures/Spells/Blood/Blood.png");
		break;
	case LIGHT:
		elementIcon.loadFromFile("Textures/Spells/Light/Light.png");
		break;
	case VOID:
		elementIcon.loadFromFile("Textures/Spells/Void/Void.png");
		break;
	}
	
	currentEleIcon.setTexture(elementIcon);


	int prevIndex = spellIndex - 1;
	if (prevIndex <= -1) prevIndex = (*spellList).size()-1;
	prevSpell = SetSpell((*spellList)[prevIndex], prevSpell);
	prevSpellIcon = prevSpell->icon;
	int nextIndex = spellIndex + 1;
	if (nextIndex >= (*spellList).size()) nextIndex = 0;
	nextSpell = SetSpell((*spellList)[nextIndex], prevSpell);
	nextSpellIcon = nextSpell->icon;
}

void SpellSlot::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {
	
	currentSpell->Fire(target, origin, enemy);
	active->push_back(currentSpell);
	currentSpell = SetSpell((*spellList)[spellIndex], currentSpell);
	bReady = false;
}

void SpellSlot::Draw(RenderWindow* window) {
	window->draw(currentBackground);
	window->draw(prevBackground,&notCurrent);
	window->draw(nextBackground,&notCurrent);
	window->draw(prevSpellIcon, &notCurrent);
	window->draw(nextSpellIcon, &notCurrent);
	
	window->draw(spellIcon);
	window->draw(cooldownIcon, &cooldownShader);
	window->draw(currentEleIcon);
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
	currentBackground.setPosition(pos);
	prevBackground.setPosition(pos + Vector2f(-20, 0));
	nextBackground.setPosition(pos + Vector2f(20, 0));


	cooldownIcon.setPosition(pos);
	spellIcon.setPosition(pos + Vector2f(8, 8));
	prevSpellIcon.setPosition(prevBackground.getPosition() + Vector2f(8, 8));
	nextSpellIcon.setPosition(nextBackground.getPosition() + Vector2f(8, 8));

	currentEleIcon.setPosition(pos + Vector2f(8,8) + Vector2f(0,18));
}

void SpellSlot::SetSpellList(vector<SPELL>* list, ELEMENT e) {
	spellList = list;
	currentElement = e;
	//cooldownTimer -= 1;

	UpdateSpells();
}