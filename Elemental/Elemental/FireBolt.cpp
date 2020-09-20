#include "FireSpells.h"

FireBolt::FireBolt() {

	
	tex.loadFromFile("Textures/Spells/Fire/FireBolt.png");
	icon.setTexture(tex);
	icon.setOrigin(4, 4);

	effectShade.loadFromFile("Textures/Shaders/effectShade.vert", Shader::Vertex);
	speed = 150;
	damage = 15;
	cooldown = 1;
	name = FIREBOLT;
	element = FIRE;
	targetType = POINT;
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

SpellEffect* FireBolt::Collide() {
	Spell::Collide();
	return new BaseCircle(icon.getPosition(), damage,element,EFFECT_STATIC,1.0f);
}