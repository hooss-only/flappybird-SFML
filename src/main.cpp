#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/scene.hpp"
#include "scenes/game_scene.hpp"

#define WIDTH 600
#define HEIGHT 1000
#define TITLE "FlappyBird"

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),TITLE);
	sf::Clock clock;
	const float fixedTimeStep = 1.0f / 60.0f; // 60 FPS

	Scene* game_scene = new GameScene();
	
	SceneManager scene_manager;
	scene_manager.set_scene(game_scene);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Exiting game..." << std::endl;
				std::cout << "Dropping heaps" << std::endl;
				scene_manager.end_game();
				std::cout << "Done!" << std::endl;
				window.close();
			}
		}
		float deltaTime = clock.restart().asSeconds();

		window.clear();
		scene_manager.event_handler(&event);
		scene_manager.tick();
		scene_manager.render(&window);
		window.display();

		sf::sleep(sf::seconds(fixedTimeStep - deltaTime));
	}

	std::cout << "Exited game!" << std::endl;
	return 0;
}
