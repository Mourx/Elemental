#include "EnemyAttack.h"


EnemyAttack::EnemyAttack() {

}

EnemyAttack::~EnemyAttack() {

}

void EnemyAttack::Update(Time t){
	if (bEffect) {
		float time = (float)t.asSeconds();
		effectTimer += time;
		float diff = (effectDuration - effectTimer) / effectDuration;
		effectShade.setUniform("time", diff);
		if (effectTimer >= effectDuration) {
			effectTimer = 0;
			bEffect = false;
			bIsFinished = true;
		}
	}

}

void EnemyAttack::Draw(RenderWindow* window) {
	if (bEffect) {
		window->draw(icon, &effectShade);
	}
	else {
		window->draw(icon);
	}
}

SpellEffect* EnemyAttack::Collide() {
	bReachedTarget = true;
	bCollided = true;
	return new SpellEffect();
}