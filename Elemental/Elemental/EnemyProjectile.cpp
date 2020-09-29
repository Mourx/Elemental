#include "EnemyAttack.h"

EnemyProjectile::EnemyProjectile(Vector2f target, Vector2f origin, float dmg, ELEMENT element) {
	tex.loadFromFile("Textures/Spells/Water/WaterBall.png");
	icon.setTexture(tex);
	icon.setOrigin(4, 4);
	targetPoint = target;
	Vector2f distance = targetPoint - origin;
	float absDist = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	ele = element;
	hDirection = distance.x / absDist;
	vDirection = distance.y / absDist;
	icon.setPosition(origin);
	bReachedTarget = false;
	effectShade.loadFromFile("Textures/Shaders/effectShade.vert", Shader::Vertex);
	speed = 150;
}

EnemyProjectile::~EnemyProjectile() {

}

void EnemyProjectile::Update(Time t) {
	EnemyAttack::Update(t);
	icon.setPosition(icon.getPosition().x + hDirection * speed*t.asSeconds(), icon.getPosition().y + vDirection * speed*t.asSeconds());
	if (abs(icon.getPosition().x - targetPoint.x) <= 1 && abs(icon.getPosition().y - targetPoint.y) <= 1) {
		bReachedTarget = true;
	}
	if (bReachedTarget) {
		bEffect = true;
		speed = 0;
	}
}

SpellEffect* EnemyProjectile::Collide() {
	EnemyAttack::Collide();
	return new BaseCircle(icon.getPosition(), damage, ele, EFFECT_STATIC, 1.0f, true);
}