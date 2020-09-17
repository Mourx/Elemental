#include "SpellEffect.h"

BaseCircle::BaseCircle(Vector2f pos,float dmg,ELEMENT type) {
	tex.loadFromFile("Textures/SpellEffects/BaseCircle.png");
	icon.setTexture(tex);
	icon.setOrigin(16, 16);
	icon.setPosition(pos);
	effectTimer = 0;
	damage = dmg;
	switch (type) {
	case FIRE:
		effectShade.loadFromFile("Textures/Shaders/effectFire.vert", Shader::Vertex);
		break;
	default:
		break;
	}
	
}

BaseCircle::~BaseCircle() {

}

void BaseCircle::Update(Time t) {
	if (bEffect) {
		float time = (float)t.asMicroseconds();
		effectTimer += time;
		float diff = (effectDuration - effectTimer) / effectDuration;
		effectShade.setUniform("time", diff);
		if (effectTimer >= effectDuration) {
			effectTimer = 0;
			bEffect = false;
		}
	}
}