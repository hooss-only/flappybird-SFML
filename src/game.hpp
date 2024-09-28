#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
	public:
		static const int WIDTH = 600;
		static const int HEIGHT = 1000;
		static sf::RenderWindow* window;
		static void init();
		static void clean();
};

#endif
