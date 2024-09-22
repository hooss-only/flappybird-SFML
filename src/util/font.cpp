#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>

#include "resource.hpp"

sf::Font* game_font = new sf::Font();

void load_font(sf::Font *font, std::string font_path) {
	font_path = get_resource_dir() + font_path;
	if (!font->loadFromFile(font_path)) {
		std::cerr << "Error Loading " << font_path << std::endl;
		exit(1);
	}
}

void load_all_fonts() {
	load_font(game_font, "fonts/DepartureMono-Regular.otf");
}

void unload_all_fonts() {
	std::cout << "dropping all fonts" << std::endl;
	if (game_font != nullptr)
		delete game_font;
	game_font = nullptr;
	std::cout << "dropped" << std::endl;
}

