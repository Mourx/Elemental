#include "Player.h"


Player::Player(TileMap* c) {
	tex.loadFromFile("Textures/Player/player.png");
	icon.setTexture(tex);
	icon.setOrigin(16, 16);

	currentMap = c;

	vector<SPELL>* waterSpells = new vector<SPELL>(0);
	vector<SPELL>* fireSpells = new vector<SPELL>(0);
	
	fireSpells->push_back(FIREBOLT);
	waterSpells->push_back(WATERBALL);
	spellTable.insert({ FIRE, fireSpells });
	spellTable.insert({ WATER, waterSpells });
	leftSpell = new SpellSlot(activeSpells, waterSpells);
	leftSpell->SetSpell((*waterSpells)[spellIndexLeft]);
	rightSpell = new SpellSlot(activeSpells, fireSpells);
	rightSpell->SetSpell((*fireSpells)[spellIndexRight]);

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
		effect->Update(t);
		if (!effect->IsFinished()) {
			activeEffects.erase(remove(activeEffects.begin(), activeEffects.end(), effect), activeEffects.end());
		}
	}
	SetPosition(position);
	leftSpell->Update(t);
	rightSpell->Update(t);

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
}

void Player::MousePressed(Vector2i pos) {
	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		if (leftSpell->IsReady()) {
			leftSpell->Fire(Vector2f(pos), icon.getPosition(), new Enemy());
			vector<SPELL>* list = spellTable[WATER];
			spellIndexLeft++;
			if (spellIndexLeft >= list->size()) {
				spellIndexLeft = 0;
			}
			leftSpell->SetSpell((*list)[spellIndexLeft]);
		}
	}
	if (Mouse::isButtonPressed(Mouse::Button::Right)) {
		if (rightSpell->IsReady()) {
			rightSpell->Fire(Vector2f(pos), icon.getPosition(), new Enemy());
			vector<SPELL>* list = spellTable[FIRE];
			spellIndexRight++;
			if (spellIndexRight >= list->size()) {
				spellIndexRight = 0;
			}
			rightSpell->SetSpell((*list)[spellIndexRight]);
		}
	}
	
}

void Player::SetPosition(Vector2f p) {
	position = p;
	icon.setPosition(position);

	leftSpell->SetPosition(p + Vector2f(-140, 100));
	rightSpell->SetPosition(p + Vector2f(-100, 100));
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
	for (SpellEffect* effect : activeEffects) {
		for (Enemy* e : currentMap->enemies) {
			if (e->icon.getGlobalBounds().intersects(effect->icon.getGlobalBounds())) {
				effect->AddEnemy(e);
			}
		}
	}
	
}