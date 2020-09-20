#include "WaterSpells.h"

WaterPulse::WaterPulse() {
	tex.loadFromFile("Textures/Spells/Water/WaterPulse.png");
	icon.setTexture(tex);
	icon.setOrigin(4, 4);

	effectShade.loadFromFile("Textures/Shaders/effectShade.vert", Shader::Vertex);
	speed = 0;
	damage = 20;
	cooldown = 0.8;

	name = WATERPULSE;
	element = WATER;
	targetType = SELF;

	effectDuration = 0.05;
}

WaterPulse::~WaterPulse() {

}

void WaterPulse::Fire(Vector2f target, Vector2f origin, Enemy* enemy) {
	targetPoint = target;
	targetEnemy = enemy;
	Vector2f distance = targetPoint - origin;
	float absDist = sqrt(pow(distance.x, 2) + pow(distance.y, 2));

	hDirection = 0;
	vDirection = 0;
	icon.setPosition(origin);
	bReachedTarget = true;
	
}


void WaterPulse::EffectUpdate(Time t) {
	if (bEffect) {
		float time = (float)t.asSeconds();
		effectTimer += time;
		float effect = (effectDuration - effectTimer) / effectDuration;
		effectShade.setUniform("time", effect);
		if (effectTimer >= effectDuration) {
			effectTimer = 0;
			bEffect = false;
			bIsFinished = true;
		}
	}
}
SpellEffect* WaterPulse::Collide() {
	Spell::Collide();
	return new BaseCircle(icon.getPosition(), damage, element, EFFECT_SELF,2.0f);
}