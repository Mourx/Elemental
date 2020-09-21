#include "TileMap.h"


TileMap::TileMap() {

}

TileMap::~TileMap() {

}

void TileMap::Draw(RenderWindow* window) {
	for (vector<Tile*> row : background) {
		for (Tile* tile : row) {

			window->draw(tile->icon);
		}
	}
	for (vector<Tile*> row : layout) {
		for (Tile* tile : row) {
			
			window->draw(tile->icon);
		}
	}
	for (Enemy* e : enemies) {
		e->Draw(window);
	}
	for (EnemyAttack* atk : (*enemyAttacks)) {
		atk->Draw(window);
	}

}