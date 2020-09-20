#include "Enemy.h"

Dummy::Dummy() {
	tex.loadFromFile("Textures/Enemy/targetDummy.png");
	icon.setTexture(tex);
	icon.setPosition(256+16, 32+16);
	icon.setOrigin(16, 16);

	health = 1000000;
}

Dummy::~Dummy() {

}