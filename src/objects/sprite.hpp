#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>

class SpriteTicker {
	public:
		SpriteTicker(sf::Sprite* sprite);
		virtual ~SpriteTicker();

		virtual void tick();

		sf::Sprite* sprite;
};

#endif
