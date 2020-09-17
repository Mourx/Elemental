#include "Player.h"


Player::Player(TileMap* c) {
	tex.loadFromFile("Textures/Player/player.png");
	icon.setTexture(tex);
	icon.setOrigin(16, 16);
	SetPosition(Vector2f(200, 200));
	currentMap = c;

	currentSpell = new SpellSlot(activeSpells);
	currentSpell->SetSpell(FIREBOLT);
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
}

void Player::Draw(RenderWindow* window) {
	window->draw(icon);
	const vector<Spell*> drawables = *activeSpells;
	for (Spell* spell : drawables) {
		spell->Draw(window);
	}
	
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
	currentSpell->Fire(Vector2f(pos), icon.getPosition(),new Enemy());
}

void Player::SetPosition(Vector2f p) {
	position = p;
	icon.setPosition(position);
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
				if (tile->icon.getGlobalBounds().intersects(spell->icon.getGlobalBounds())) {
					spell->Collide();
				}
			}
		}
		for (Enemy* e : currentMap->enemies) {
			if (e->icon.getGlobalBounds().intersects(spell->icon.getGlobalBounds())) {
				spell->Collide();
			}
		}
	}
	
}