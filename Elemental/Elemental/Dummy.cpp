#include "Enemy.h"

Dummy::Dummy() {
	tex.loadFromFile("Textures/Enemy/targetDummy.png");
	icon.setTexture(tex);
	icon.setPosition(256, 32);
}

Dummy::~Dummy() {

}