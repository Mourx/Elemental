#include "Enemy.h"


Enemy::Enemy() {


	damageShade.loadFromFile("Textures/Shaders/effectDamageFlash.vert", Shader::Vertex);
}


Enemy::~Enemy() {

}

void Enemy::Draw(RenderWindow* window) {
	if (bDamageFlash) {
		window->draw(icon, &damageShade);
	}
	else {
		window->draw(icon);
	}
}

void Enemy::Update(Time t) {
	if (bDamageFlash) {
		float time = t.asSeconds();
		flashTimer += time;
		if (flashTimer >= flashDuration) {
			bDamageFlash = false;
			flashTimer = 0;
		}
	}
}

void Enemy::Damage(float dmg) {
	health -= dmg;
	if (health <= 0) {
		health = 0;
		bDead = true;
	}
	else {
		bDamageFlash = true;
	}
	printf("%2.0f damage taken, %2.0f health left\n", dmg, health);
}