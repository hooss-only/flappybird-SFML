#include <SFML/Graphics.hpp>
#include "sprite.hpp"

SpriteTicker::SpriteTicker(sf::Sprite* sprite) {
	this->sprite = sprite;
}
SpriteTicker::~SpriteTicker() {}
void SpriteTicker::tick() {}
