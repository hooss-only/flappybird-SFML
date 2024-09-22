#include <SFML/Graphics.hpp>
#include <iostream>

#include "util/font.hpp"
#include "objects/scene.hpp"
#include "objects/event.hpp"
#include "scenes/game_scene.hpp"
#include "scenes/game_over_scene.hpp"

#define WIDTH 600
#define HEIGHT 1000
#define TITLE "FlappyBird"

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),TITLE); sf::Clock clock;
	const float fixedTimeStep = 1.0f / 60.0f; // 60 FPS
	
	load_all_fonts();

	SceneManager scene_manager;

	Scene* game_scene = new GameScene();
	Scene* game_over_scene = new GameOverScene();

	scene_manager.set_scene(game_scene);

	state = "";

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

		if (state == "player_dead") {
			scene_manager.change_scene(game_over_scene);
			std::cout << "player_dead" << std::endl;
			state = "game_end";
		}

		window.clear();
		std::cout << "hi" << std::endl;
		scene_manager.event_handler(&event);
		std::cout << "hi" << std::endl;
		scene_manager.tick();
		std::cout << "hi" << std::endl;
		scene_manager.render(&window);
		std::cout << "hi" << std::endl;
		window.display();

		sf::sleep(sf::seconds(fixedTimeStep - deltaTime));
	}

	unload_all_fonts();
	delete game_scene;
	delete game_over_scene;

	std::cout << "Exited game!" << std::endl;
	return 0;
}
