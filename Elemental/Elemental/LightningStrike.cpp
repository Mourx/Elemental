#include "AirSpells.h"

LightningStrike::LightningStrike() {
	tex.loadFromFile("Textures/Spells/Air/LightningStrike.png");
	icon.setTexture(tex);
	icon.setOrigin(4, 4);

	effectShade.loadFromFile("Textures/Shaders/effectShade.vert", Shader::Vertex);
	speed = 30;
	damage = 2;
	cooldown = 0.3;

	name = WATERBALL;
	element = WATER;
	targetType = ENEMY;
}

LightningStrike::~LightningStrike() {

}

void LightningStrike::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {
	targetPoint = target;
	targetEnemy = enemy;
	Vector2f distance = target - origin;
	float absDist = sqrt(pow(distance.x, 2) + pow(distance.y, 2));

	hDirection = distance.x / absDist;
	vDirection = distance.y / absDist;
	icon.setPosition(origin);
	bReachedTarget = false;
}


void LightningStrike::EffectUpdate(Time t) {
	/*if (bEffect) {
		float time = (float)t.asMicroseconds();
		effectTimer += time;
		effectShade.setUniform("time", (effectDuration - effectTimer) / effectDuration);
		if (effectTimer >= effectDuration) {
			effectTimer = 0;
			bEffect = false;
			bIsFinished = true;
		}
	}*/
	bEffect = false;
	bIsFinished = true;
}
SpellEffect* LightningStrike::Collide() {
	Spell::Collide();
	return new BaseCircle(icon.getPosition(), damage, element,EFFECT_STATIC,1.0f);
}