#pragma once
#include <vector>
#include "Tile.h"
#include "enums.h"
#include "Enemy.h"

using namespace std;
class TileMap
{
public:
	TileMap();
	~TileMap();
	void Draw(RenderWindow* window);
	vector<vector<Tile*>> layout;
	vector<Enemy*> enemies;

protected:
	vector<vector<Tile*>> background;
	map<string,Texture> textures;
	map<string, PATHING> pathing;
	Texture backgroundTex;
};

class TreeTown : public TileMap
{
public:
	TreeTown();
	~TreeTown();
};