#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TileMap.h"
#include "Enemy.h"
#include "icon.h"
using namespace sf;
using namespace std;

int main() {
	RenderWindow window(VideoMode(960, 960), "Time for elements!");
	Clock clock;
	TileMap* currentMap;
	currentMap = new TreeTown();
	Player* player = new Player(currentMap);
	window.setIcon(gimp_image.width,gimp_image.height,gimp_image.pixel_data);
	View camera = window.getDefaultView();
	camera.zoom(1);
	bool bMouseHeld = false;
	while (window.isOpen()) {
		window.setView(camera);
		sf::Time elapsed = clock.restart();
		Event event;
		player->Update(elapsed);
		camera.setCenter(player->GetPosition());
		camera.setSize(320,320);
		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed ) {
				bMouseHeld = true;
				Vector2i coOrds = Vector2i(window.mapPixelToCoords(Mouse::getPosition(window)));
				player->MousePressed(coOrds);
			}
			if (event.type == Event::MouseButtonReleased) {
				if (!(Mouse::isButtonPressed(Mouse::Button::Left) || Mouse::isButtonPressed(Mouse::Button::Right))) {
					bMouseHeld = false;
				}
			}
		}
		if (bMouseHeld) {
			Vector2i coOrds = Vector2i(window.mapPixelToCoords(Mouse::getPosition(window)));
			player->MousePressed(coOrds);
		}
		window.clear(Color::Black);
		currentMap->Draw(&window);
		player->Draw(&window);


		window.display();
	}
	return 0;
}