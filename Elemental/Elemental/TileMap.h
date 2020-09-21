#pragma once
#include <vector>
#include "Tile.h"
#include "enums.h"
#include "Enemy.h"
#include "WaterEnemies.h"
using namespace std;
class TileMap
{
public:
	TileMap();
	~TileMap();
	void Draw(RenderWindow* window);
	virtual void Setup(){}
	vector<vector<Tile*>> layout;
	vector<Enemy*> enemies;
	vector<EnemyAttack*>* enemyAttacks = new vector<EnemyAttack*>(0);
	void SetPlayer(Player* p) { player = p; this->Setup(); }
protected:
	vector<vector<Tile*>> background;
	map<string,Texture> textures;
	map<string, PATHING> pathing;
	Texture backgroundTex;
	Player* player;
};

class TreeTown : public TileMap
{
public:
	TreeTown();
	~TreeTown();
	void Setup();
};