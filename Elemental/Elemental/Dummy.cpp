#include "Enemy.h"

Dummy::Dummy() {
	tex.loadFromFile("Textures/Enemy/targetDummy.png");
	icon.setTexture(tex);
	icon.setPosition(256+16, 32+16);
	icon.setOrigin(16, 16);
	element = VOID;
	health = 1000000;
}

Dummy::~Dummy() {

}