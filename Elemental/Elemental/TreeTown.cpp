#include "TileMap.h"

TreeTown::TreeTown() {
	string tilemapPath = "Textures/Tilemaps/TreeTown.png";
	backgroundTex.loadFromFile(tilemapPath, IntRect(0, 0, 32, 32));
	for (int i = 0; i < 10; i++) {
		vector<Tile*> tiles;
		for (int j = 0; j < 10; j++) {
			tiles.push_back(new Tile(backgroundTex, Vector2f((float)i * 32, (float)j * 32),PATHABLE));
		}
		background.push_back(tiles);
	}
	Texture tex;

	//load tree
	tex.loadFromFile(tilemapPath, IntRect(0, 32, 32, 32));
	textures.insert({ "tree", tex });
	pathing.insert({ "tree", NOT_PATHABLE });

	//house top left
	tex.loadFromFile(tilemapPath, IntRect(32, 0, 32, 32));
	textures.insert({ "houseTL", tex });
	pathing.insert({ "houseTL", NOT_PATHABLE });

	//house top right
	tex.loadFromFile(tilemapPath, IntRect(64, 0, 32, 32));
	textures.insert({ "houseTR", tex });
	pathing.insert({ "houseTR", NOT_PATHABLE });

	//house bottom left
	tex.loadFromFile(tilemapPath, IntRect(32, 32, 32, 32));
	textures.insert({ "houseBL", tex });
	pathing.insert({ "houseBL", DOORWAY });

	//house bottom right
	tex.loadFromFile(tilemapPath, IntRect(64, 32, 32, 32));
	textures.insert({ "houseBR", tex });
	pathing.insert({ "houseBR", NOT_PATHABLE });

	//well
	tex.loadFromFile(tilemapPath, IntRect(96, 0, 32, 32));
	textures.insert({ "well",tex });
	pathing.insert({ "well", NOT_PATHABLE });

	string layoutString[10][10] = {
	{"tree","tree","tree","tree","tree","empty","empty","tree","tree","tree"},
	{"tree","houseTL","houseTR","empty","empty","empty","empty","empty","empty","tree"},
	{"tree","houseBL","houseBR","empty","empty","empty","empty","empty","empty","tree"},
	{"tree","empty","empty","empty","empty","empty","empty","empty","empty","tree"},
	{"tree","empty","empty","empty","empty","empty","empty","empty","empty","tree"},
	{"tree","tree","tree","empty","empty","empty","empty","empty","empty","tree"},
	{"tree","tree","tree","empty","empty","empty","empty","empty","empty","tree"},
	{"tree","empty","empty","empty","tree","tree","empty","empty","empty","tree"},
	{"tree","well","empty","empty","tree","tree","empty","empty","empty","tree"},
	{"tree","tree","tree","tree","tree","tree","tree","tree","tree","tree"},
	};
	for (int i = 0; i < 10; i++) {
		vector<Tile*> tiles;
		for (int j = 0; j < 10; j++) {
			string type = layoutString[j][i];
			tiles.push_back(new Tile(textures[type], Vector2f((float)i * 32, (float)j * 32),pathing[type]));
		}
		layout.push_back(tiles);
	}


	enemies.push_back(new Dummy());
}

TreeTown::~TreeTown() {

}