#include "SpellEffect.h"

BaseCircle::BaseCircle(Vector2f pos,float dmg,ELEMENT ele, EFFECT_TYPE effType,float size, bool bIsEnemy) {
	tex.loadFromFile("Textures/SpellEffects/BaseCircle.png");
	icon.setTexture(tex);
	icon.setOrigin(16, 16);
	icon.setPosition(pos);
	effectTimer = 0;
	icon.setScale(size,size);
	damage = dmg;
	type = effType;
	element = ele;
	bEnemySource = bIsEnemy;
	switch (element) {
	case FIRE:
		effectShade.loadFromFile("Textures/Shaders/effectFire.vert", Shader::Vertex);
		break;
	case WATER:
		effectShade.loadFromFile("Textures/Shaders/effectWater.vert", Shader::Vertex);
		break;
	default:
		break;
	}
	
}

BaseCircle::~BaseCircle() {

}

void BaseCircle::Update(Time t) {
	if (bEffect) {
		float time = (float)t.asSeconds();
		effectTimer += time;
		float diff = (effectDuration - effectTimer) / effectDuration;
		effectShade.setUniform("time", diff);
		if (effectTimer >= effectDuration) {
			effectTimer = 0;
			bEffect = false;
		}
	}
}