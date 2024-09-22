#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>

class SpriteTicker {
	public:
		SpriteTicker();
		virtual ~SpriteTicker();

		virtual void tick();
		
		int depth;
		bool visible;
		bool ticking;
		sf::Drawable* sprite;
		sf::Texture* texture_ptr;

	private:
		void drop();
};

#endif
