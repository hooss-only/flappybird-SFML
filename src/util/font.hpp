#ifndef FONT_HPP
#define FONT_HPP

#include <SFML/Graphics.hpp>
#include <string>

void load_font(sf::Font *font, std::string font_path);

extern sf::Font* game_font;

void load_all_fonts();

void unload_all_fonts();

#endif
