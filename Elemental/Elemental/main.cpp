#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TileMap.h"
#include "Enemy.h"
using namespace sf;
using namespace std;

int main() {
	RenderWindow window(VideoMode(960, 960), "Time for elements!");
	Clock clock;
	TileMap* currentMap;
	currentMap = new TreeTown();
	Player* player = new Player(currentMap);

	View camera = window.getDefaultView();
	camera.zoom(1);
	
	while (window.isOpen()) {
		window.setView(camera);
		sf::Time elapsed = clock.restart();
		Event event;
		player->Update(elapsed);
		camera.setCenter(player->GetPosition());
		camera.setSize(320,320);
		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed) {

			}
		}
		window.clear(Color::Black);
		currentMap->Draw(&window);
		window.draw(player->icon);


		window.display();
	}
	return 0;
}