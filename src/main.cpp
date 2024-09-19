#include <SFML/Graphics.hpp>
#include <iostream>

#include "objects/sprite.hpp"
#include "objects/scene.hpp"

#define WIDTH 600
#define HEIGHT 800
#define TITLE "FlappyBird"

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),TITLE);

	Scene test_scene;

	sf::Texture test_texture;
	if (!test_texture.loadFromFile("arch-rainbow.jpg")) {
  	std::cerr << "Error loading player.png" << std::endl;
  	return -1;
	}

	sf::Sprite test_sprite;

	SpriteTicker test_sprite_ticker(&test_sprite);

	test_scene.add_sprite_ticker(&test_sprite_ticker);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		test_scene.render(&window);
		window.display();
	}

	return 0;
}
