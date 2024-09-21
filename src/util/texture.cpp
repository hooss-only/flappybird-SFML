#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "resource.hpp"

void load_texture(sf::Texture* texture, std::string image_path) {
	image_path = get_resource_dir() + image_path;
	if (!texture->loadFromFile(image_path)) {
		std::cerr << "Error Loading " << image_path << std::endl;
		exit(1);
	}
}
