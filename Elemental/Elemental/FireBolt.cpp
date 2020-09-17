#include "FireSpells.h"

FireBolt::FireBolt() {

	
	tex.loadFromFile("Textures/Spells/Fire/FireBolt.png");
	icon.setTexture(tex);
	icon.setOrigin(4, 4);

	effectShade.loadFromFile("Textures/shaders/effectShade.vert", Shader::Vertex);
	speed = 150;
	damage = 5;
}

FireBolt::~FireBolt() {

}

void FireBolt::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {
	targetPoint = target;
	targetEnemy = enemy;
	Vector2f distance = target - origin;
	float absDist = sqrt(pow(distance.x, 2) + pow(distance.y,2));
	
	hDirection = distance.x/absDist;
	vDirection = distance.y / absDist;
	icon.setPosition(origin);
	bReachedTarget = false;
}

void FireBolt::EffectUpdate(Time t) {
	if (bEffect) {
		float time = (float)t.asMicroseconds();
		effectTimer += time;
		effectShade.setUniform("time", (effectDuration - effectTimer) / effectDuration);
		if (effectTimer >= effectDuration) {
			effectTimer == 0;
			bEffect = false;
			bIsFinished = true;
		}
	}
}