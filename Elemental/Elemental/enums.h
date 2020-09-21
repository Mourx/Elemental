#pragma once


enum PATHING {
	PATHABLE,
	NOT_PATHABLE,
	DOORWAY
};

enum ELEMENT {
	FIRE,
	WATER,
	EARTH,
	AIR,
	BLOOD,
	SOUL,
	VOID
};

enum TARGET_TYPE {
	POINT,
	ENEMY,
	SELF
};

enum EFFECT_TYPE {
	EFFECT_SELF,
	EFFECT_STATIC
};

enum SPELL {
	FIREBOLT,
	WATERBALL,
	WATERPULSE,
	LIGHTNINGSTRIKE
};


static struct {
	float matchups[7][7] = {
		{0.5,0.5,1,1.5,1,1,1.5},
		{1.5,0.5,0.5,1,1,1,1.5},
		{1,1.5,0.5,0.5,1,1,1.5},
		{0.5,1,1.5,0.5,1,1,1.5},
		{1,1,1,1,1.5,1.5,1.5},
		{1,1,1,1,1.5,1.5,1.5},
		{1.5,1.5,1.5,1.5,1.5,1.5,0}
	};
	float GetMultiplier(ELEMENT spellType, ELEMENT targetType) {
		float multiplier = matchups[(int)spellType][(int)targetType];
		return multiplier;
	}
}matchups;