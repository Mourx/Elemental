#include "WaterEnemies.h"

Slime::Slime(vector<EnemyAttack*>* atts,Player* p) {
	tex.loadFromFile("Textures/Enemy/Water/Slime.png");
	icon.setTexture(tex);
	player = p;
	health = 100;
	element = WATER;
	icon.setOrigin(8, 8);
	attacks = atts;
	damage = 3;
}


Slime::~Slime() {

}

void Slime::Attack(Player* player) {
	attacks->push_back(new EnemyProjectile(player->icon.getPosition(), this->icon.getPosition(), damage, element));
}