#include "Enemy.h"


Enemy::Enemy() {

}


Enemy::~Enemy() {

}

void Enemy::Draw(RenderWindow* window) {
	window->draw(icon);
}