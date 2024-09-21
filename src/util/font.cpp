#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

#include "resource.hpp"

void load_font(sf::Font *font, std::string font_path) {
	font_path = get_resource_dir() + font_path;
	if (!font->loadFromFile(font_path)) {
		std::cerr << "Error Loading " << font_path << std::endl;
		exit(1);
	}
}
