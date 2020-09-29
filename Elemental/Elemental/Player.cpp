#include "Player.h"


Player::Player(TileMap* c) {
	tex.loadFromFile("Textures/Player/player.png");
	icon.setTexture(tex);
	icon.setOrigin(16, 16);

	currentMap = c;
	currentMap->SetPlayer(this);

	leftBackTex.loadFromFile("Textures/Spells/SpellSlots/SpellSlot_BackLayerLeft.png");
	rightBackTex.loadFromFile("Textures/Spells/SpellSlots/SpellSlot_BackLayerLeft.png");
	SpellBackLayerLeft.setTexture(leftBackTex);
	SpellBackLayerRight.setTexture(rightBackTex);



	vector<SPELL>* waterSpells = new vector<SPELL>(0);
	vector<SPELL>* fireSpells = new vector<SPELL>(0);
	vector<SPELL>* earthSpells = new vector<SPELL>(0);
	vector<SPELL>* airSpells = new vector<SPELL>(0);
	vector<SPELL>* bloodSpells = new vector<SPELL>(0);
	vector<SPELL>* soulSpells = new vector<SPELL>(0);
	vector<SPELL>* voidSpells = new vector<SPELL>(0);
	elementOrder = { FIRE,WATER,EARTH,AIR,BLOOD,SOUL,VOID };
	
	fireSpells->push_back(FIREBOLT);
	spellTable.insert({ FIRE, fireSpells });
	currentElements.push_back(FIRE);

	waterSpells->push_back(WATERBALL);
	waterSpells->push_back(WATERPULSE);
	spellTable.insert({ WATER, waterSpells });
	currentElements.push_back(WATER);

	spellTable.insert({ EARTH,earthSpells });

	airSpells->push_back(LIGHTNINGSTRIKE);
	spellTable.insert({ AIR,airSpells });
	currentElements.push_back(AIR);

	spellTable.insert({ BLOOD,bloodSpells });
	spellTable.insert({ SOUL,soulSpells });
	spellTable.insert({ VOID,voidSpells });

	leftSpell = new SpellSlot(activeSpells, spellTable[elementOrder[leftElementIndex]], elementOrder[leftElementIndex]);
	//leftSpell->SetSpell((*waterSpells)[spellIndexLeft]);
	rightSpell = new SpellSlot(activeSpells, spellTable[elementOrder[rightElementIndex]], elementOrder[rightElementIndex]);
	//rightSpell->SetSpell((*fireSpells)[spellIndexRight]);

	SetPosition(Vector2f(200, 200));
}

Player::~Player() {

}

void Player::Update(Time t) {
	CheckKeys(t);
	UpdateCollisions();

	for (Spell* spell : *activeSpells) {
		spell->Update(t);
		if (spell->IsFinished()) {
			activeSpells->erase(remove(activeSpells->begin(), activeSpells->end(), spell), activeSpells->end());
		}
	}
	for (SpellEffect* effect : activeEffects) {
		if (effect->GetType() == EFFECT_SELF) {
			effect->icon.setPosition(position);
		}
		effect->Update(t);
		if (!effect->IsFinished()) {
			activeEffects.erase(remove(activeEffects.begin(), activeEffects.end(), effect), activeEffects.end());
		}
	}
	for (Enemy* e : currentMap->enemies) {
		e->Update(t);
		if (e->IsDead()) {
			currentMap->enemies.erase(remove(currentMap->enemies.begin(), currentMap->enemies.end(), e), currentMap->enemies.end());
		}
	
	}
	for (EnemyAttack* atk : *(currentMap->enemyAttacks)) {
		atk->Update(t);
		vector<EnemyAttack*>* attacks = (currentMap->enemyAttacks);
		if (atk->IsFinished()) {
			attacks->erase(remove(attacks->begin(), attacks->end(), atk), attacks->end());
		}
	}


	SetPosition(position);
	leftSpell->Update(t);
	rightSpell->Update(t);

	if (bSwitchedSpellLeft) {
		float time = t.asSeconds();
		spellSwitchTimerLeft += time;
		if (spellSwitchTimerLeft >= spellSwitchCooldown) {
			bSwitchedSpellLeft = false;
			spellSwitchTimerLeft = 0;
		}
	}

	if (bSwitchedSpellRight) {
		float time = t.asSeconds();
		spellSwitchTimerRight += time;
		if (spellSwitchTimerRight >= spellSwitchCooldown) {
			bSwitchedSpellRight = false;
			spellSwitchTimerRight = 0;
		}
	}

	if (bSwitchedElementLeft) {
		float time = t.asSeconds();
		elementSwitchTimerLeft += time;
		if (elementSwitchTimerLeft >= elementSwitchCooldown) {
			bSwitchedElementLeft = false;
			elementSwitchTimerLeft = 0;
		}
	}

	if (bSwitchedElementRight) {
		float time = t.asSeconds();
		elementSwitchTimerRight += time;
		if (elementSwitchTimerRight >= elementSwitchCooldown) {
			bSwitchedElementRight = false;
			elementSwitchTimerRight = 0;
		}
	}

}

void Player::Draw(RenderWindow* window) {
	window->draw(icon);
	const vector<Spell*> drawables = *activeSpells;
	for (Spell* spell : drawables) {
		spell->Draw(window);
	}
	for (SpellEffect* effect : activeEffects) {
		effect->Draw(window);
	}
	window->draw(SpellBackLayerLeft);
	window->draw(SpellBackLayerRight);

	leftSpell->Draw(window);
	rightSpell->Draw(window);
	
}

void Player::CheckKeys(Time t) {
	if(Keyboard::isKeyPressed(Keyboard::A)) {
		CheckMove(Vector2f(GetPosition().x - HSpeed * t.asSeconds(), GetPosition().y));
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		CheckMove(Vector2f(GetPosition().x + HSpeed * t.asSeconds(), GetPosition().y));
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		CheckMove(Vector2f(GetPosition().x, GetPosition().y - VSpeed * t.asSeconds()));
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		CheckMove(Vector2f(GetPosition().x, GetPosition().y + VSpeed * t.asSeconds()));
	}

	if(Keyboard::isKeyPressed(Keyboard::Q)){
		if (!bSwitchedSpellLeft) {
			leftSpell->NextSpell();
			bSwitchedSpellLeft = true;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::E)) {
		if (!bSwitchedSpellRight) {
			rightSpell->NextSpell();
			bSwitchedSpellRight = true;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::C)) {
		if (!bSwitchedElementLeft) {
			NextElementLeft();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::V)) {
		if (!bSwitchedElementRight) {
			NextElementRight();
		}
	}
}

void Player::MousePressed(Vector2i pos) {
	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		if (leftSpell->IsReady()) {
			if (leftSpell->GetTargetType() == ENEMY) {
				for (Enemy* e : currentMap->enemies) {
					if (e->icon.getGlobalBounds().contains(Vector2f(pos))) {
						leftSpell->Fire(Vector2f(pos), icon.getPosition(), e);
						break;
					}
				}
			}
			else {
				leftSpell->Fire(Vector2f(pos), icon.getPosition(), new Enemy());
			}
		
		}
	}
	if (Mouse::isButtonPressed(Mouse::Button::Right)) {
		if (rightSpell->IsReady()) {
			if (rightSpell->GetTargetType() == ENEMY) {
				for (Enemy* e : currentMap->enemies) {
					if (e->icon.getGlobalBounds().contains(Vector2f(pos))) {
						rightSpell->Fire(Vector2f(pos), icon.getPosition(), e);
						break;
					}
				}
			}
			else {
				rightSpell->Fire(Vector2f(pos), icon.getPosition(), new Enemy());
			}
		}
	}
	SetPosition(position);
}

void Player::SetPosition(Vector2f p) {
	position = p;
	icon.setPosition(position);

	Vector2f leftpos = p + Vector2f(-160, 96);
	Vector2f rightpos = p + Vector2f(96, 96);
	SpellBackLayerLeft.setPosition(leftpos);
	SpellBackLayerRight.setPosition(rightpos);


	leftSpell->SetPosition(leftpos + Vector2f(24, 27));
	rightSpell->SetPosition(rightpos + Vector2f(24, 27));
}

void Player::CheckMove(Vector2f p) {
	bool bPrevented = false;
	Sprite moveAttempt = icon;
	moveAttempt.setPosition(p);
	moveAttempt.setOrigin(16, 16);
	moveAttempt.setScale(0.8f, 0.8f);
	
	for (vector<Tile*> rows : currentMap->layout) {
		for (Tile* tile : rows) {
			if (tile->icon.getGlobalBounds().intersects(moveAttempt.getGlobalBounds())) {
				switch (tile->IsPathable()) {
				case PATHABLE:
					SetPosition(p);
					break;
				case NOT_PATHABLE:
					bPrevented = true;
					break;
				case DOORWAY:
					break;
				}
			}
		}
	}
	for (Enemy* e : currentMap->enemies) {
		if (e->icon.getGlobalBounds().intersects(moveAttempt.getGlobalBounds())) {
			bPrevented = true;
		}
	}
	if (bPrevented == false) {
		SetPosition(p);
	}
}

void Player::UpdateCollisions() {
	for (Spell* spell : *activeSpells) {
		if (!spell->HasCollided() && spell->GetType() == SELF) {
			activeEffects.push_back(spell->Collide());
		}
		else {
			for (vector<Tile*> rows : currentMap->layout) {
				for (Tile* tile : rows) {
					if (!spell->HasCollided() && tile->icon.getGlobalBounds().intersects(spell->icon.getGlobalBounds())) {
						activeEffects.push_back(spell->Collide());
					}
				}
			}
			for (Enemy* e : currentMap->enemies) {
				if (!spell->HasCollided() && e->icon.getGlobalBounds().intersects(spell->icon.getGlobalBounds())) {
					activeEffects.push_back(spell->Collide());
				}
			}
		}
	}
	for (SpellEffect* effect : activeEffects) {
		for (Enemy* e : currentMap->enemies) {
			if (!effect->IsEnemyAttack() && e->icon.getGlobalBounds().intersects(effect->icon.getGlobalBounds())) {
				effect->AddEnemy(e);
			}
			else {
				if (this->icon.getGlobalBounds().intersects(effect->icon.getGlobalBounds())) {
					//damage player;
				}
			}
		}
	}
	for (EnemyAttack* atk : *(currentMap->enemyAttacks)) {
		for (vector<Tile*> rows : currentMap->layout) {
			for (Tile* tile : rows) {
				if (!atk->HasCollided() && tile->icon.getGlobalBounds().intersects(atk->icon.getGlobalBounds())) {
					activeEffects.push_back(atk->Collide());
				}
			}
			if (!atk->HasCollided() && this->icon.getGlobalBounds().intersects(atk->icon.getGlobalBounds())) {
				activeEffects.push_back(atk->Collide());
			}
			if (!atk->HasCollided() && atk->ReachedTarget()) {
				activeEffects.push_back(atk->Collide());
			}
		}
	}
	
}

void Player::NextElementLeft() {
	leftElementIndex++;
	while (spellTable[elementOrder[leftElementIndex]]->size() == 0 || leftElementIndex == rightElementIndex) {
		leftElementIndex++;
		if (leftElementIndex >= elementOrder.size()) leftElementIndex = 0;

	}
	leftSpell->SetSpellList(spellTable[elementOrder[leftElementIndex]], elementOrder[leftElementIndex]);
	bSwitchedElementLeft = true;
}

void Player::NextElementRight() {
	rightElementIndex++;
	while (spellTable[elementOrder[rightElementIndex]]->size() == 0 || leftElementIndex == rightElementIndex) {
		rightElementIndex++;
		if (rightElementIndex >= elementOrder.size()) rightElementIndex = 0;

	}
	rightSpell->SetSpellList(spellTable[elementOrder[rightElementIndex]], elementOrder[rightElementIndex]);
	bSwitchedElementRight = true;
}