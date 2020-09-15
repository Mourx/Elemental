#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"
using namespace sf;
using namespace std;
class Tile
{
public:
	Tile(Texture t, Vector2f pos, PATHING bPath);
	~Tile();
	Sprite icon;
	PATHING IsPathable() { return bPathable; }
private:
	Texture tex;
	PATHING bPathable;
};

