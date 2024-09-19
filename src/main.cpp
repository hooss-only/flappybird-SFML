#include <SFML/Graphics.hpp>

#include "objects/scene.hpp"
#include "scenes/game_scene.hpp"

#define WIDTH 600
#define HEIGHT 800
#define TITLE "FlappyBird"

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),TITLE);

	Scene* game_scene = new GameScene();
	
	SceneManager scene_manager;
	scene_manager.set_scene(game_scene);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		scene_manager.render(&window);
		window.display();
	}

	return 0;
}
