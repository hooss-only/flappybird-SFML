#include <SFML/Graphics.hpp>
#include <iostream>

#include "util/font.hpp"
#include "objects/scene.hpp"
#include "scenes/game_scene.hpp"
#include "scenes/game_over_scene.hpp"
#include "game.hpp"

#define WIDTH 600
#define HEIGHT 1000
#define TITLE "FlappyBird"

int main() {
	Game::init();
	sf::Clock clock;
	const float fixedTimeStep = 1.0f / 60.0f; // 60 FPS
	
	load_all_fonts();

	SceneManager scene_manager;

	Scene* game_scene = new GameScene();
	Scene* game_over_scene = new GameOverScene();

	scene_manager.set_scene(game_scene);

	Game::state = GameState::NONE;

	while (Game::window->isOpen()) {
		sf::Event event;
		while (Game::window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				std::cout << "Exiting game..." << std::endl;
				std::cout << "Dropping heaps" << std::endl;
				scene_manager.end_game();
				std::cout << "Done!" << std::endl;
				Game::window->close();
			}
		}
		float deltaTime = clock.restart().asSeconds();

		switch (Game::state) {
			case (GameState::PLAYER_DEAD):
				scene_manager.change_scene(game_over_scene);
				std::cout << "player_dead" << std::endl;
				Game::state = GameState::GAME_END;
				break;
			case (GameState::RESTART):
				scene_manager.change_scene(game_scene);
				Game::state = GameState::NONE;
				break;
			default:
				break;
		}
		
		Game::window->clear();
		scene_manager.event_handler(&event);
		scene_manager.tick();
		scene_manager.render(Game::window);
		Game::window->display();

		sf::sleep(sf::seconds(fixedTimeStep - deltaTime));
	}

	unload_all_fonts();
	delete game_scene;
	delete game_over_scene;

	Game::clean();

	std::cout << "Exited game!" << std::endl;
	return 0;
}
