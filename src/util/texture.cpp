#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>

void load_texture(sf::Texture* texture, std::string image_path) {
	image_path = "Resources/" + image_path;
	if (!texture->loadFromFile(image_path)) {
		std::cerr << "Error Loading " << image_path << std::endl;
		exit(1);
	}
}
