#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	Sprite icon;
	void Draw(RenderWindow* window);
protected:
	Texture tex;
};

class Dummy : public Enemy
{
public:
	Dummy();
	~Dummy();
};