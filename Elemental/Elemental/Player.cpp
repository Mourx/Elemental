#include "Player.h"


Player::Player(TileMap* c) {
	tex.loadFromFile("Textures/Player/player.png");
	icon.setTexture(tex);
	icon.setOrigin(16, 16);
	SetPosition(Vector2f(200, 200));
	currentMap = c;
}

Player::~Player() {

}

void Player::Update(Time t) {
	CheckKeys(t);
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

void Player::SetPosition(Vector2f p) {
	position = p;
	icon.setPosition(position);
}

void Player::CheckMove(Vector2f p) {
	bool bPrevented = false;
	Sprite moveAttempt = icon;
	moveAttempt.setPosition(p);
	moveAttempt.setOrigin(16, 16);
	moveAttempt.setScale(0.8, 0.8);
	
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