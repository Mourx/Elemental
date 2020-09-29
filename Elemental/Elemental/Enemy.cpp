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
	if (!bCanAttack) {
		float time = t.asSeconds();
		attackTimer += time;
		if (attackTimer >= attackRate) {
			bCanAttack = true;
			attackTimer = 0;
		}
	}
	if (bCanAttack) {
		this->Attack(player);
		bCanAttack = false;
	}
	if (!bCanMove) {
		float time = t.asSeconds();
		moveTimer += time;
		if (moveTimer >= moveDelay) {
			bCanMove = true;
			moveTimer = 0;
			HSpeed = 2 * rand() % 5 * sin(rand() % 90);
			VSpeed = 2 * rand() % 5 * sin(rand() % 90);
		}
	}
	if (bCanMove) {
		icon.setPosition(icon.getPosition() + Vector2f(HSpeed, VSpeed));
	}

}

void Enemy::Move() {

}

void Enemy::Damage(float dmg,ELEMENT spellType) {
	float multi = matchups.GetMultiplier(spellType, this->element);
	float totalDmg = dmg * multi;
	health -= totalDmg;
	if (health <= 0) {
		health = 0;
		bDead = true;
	}
	else {
		bDamageFlash = true;
	}
	printf("%2.0f damage taken, %2.0f health left\n", totalDmg, health);
}