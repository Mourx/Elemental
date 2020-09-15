#include "Tile.h"

Tile::Tile(Texture t, Vector2f pos, PATHING bPath) {
	tex = t;
	icon.setTexture(tex);
	icon.setPosition(pos);
	bPathable = bPath;
}

Tile::~Tile() {

}