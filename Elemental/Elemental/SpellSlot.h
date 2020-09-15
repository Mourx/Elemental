#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class SpellSlot
{
public:
	SpellSlot();
	~SpellSlot();
	Sprite icon;
protected:
	Texture tex;
};

