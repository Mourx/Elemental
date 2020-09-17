#include "Spell.h"

Spell::Spell() {
	effectShade.loadFromFile("Textures/shaders/effectShade.vert", Shader::Vertex);
}

Spell::~Spell() {

}

void Spell::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {

}


void Spell::Update(Time t) {
	if (targetType == POINT) {
		// travel to target point
		icon.setPosition(icon.getPosition().x+hDirection*speed*t.asSeconds(), icon.getPosition().y + vDirection * speed*t.asSeconds());
	}
	if (targetType == ENEMY) {
		// just be cast immediately, no travel effect
	}
	if (abs(icon.getPosition().x - targetPoint.x) <= 1 && abs(icon.getPosition().y - targetPoint.y) <= 1) {
		bReachedTarget = true;
	}
	if (bReachedTarget) {
		bEffect = true;
		speed = 0;
	}
	this->EffectUpdate(t);
}

void Spell::Draw(RenderWindow* window) {
	if (bEffect) {
		window->draw(icon, &effectShade);
	}
	else {
		window->draw(icon);
	}
}

void Spell::Collide() {
	bReachedTarget = true;
}

void Spell::EffectUpdate(Time t) {

}