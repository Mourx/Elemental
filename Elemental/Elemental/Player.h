#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
using namespace sf;
using namespace std;
class Player
{
public:
	Player(TileMap* c);
	~Player();
	void Update(Time t);
	void SetPosition(Vector2f p);
	Vector2f GetPosition() { return position; };
	Sprite icon;
private:
	Texture tex;
	TileMap* currentMap;
	void CheckKeys(Time t);
	void CheckMove(Vector2f pos);
	Vector2f position;
	float HSpeed = 45;
	float VSpeed = 45;
};

