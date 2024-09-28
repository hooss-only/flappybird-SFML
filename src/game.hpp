#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

enum GameState {
	NONE,
	PLAYER_DEAD,
	GAME_END,
	RESTART,
};

class Game {
	public:
		static const int WIDTH = 600;
		static const int HEIGHT = 1000;
		static int score;
		static sf::RenderWindow* window;
		static GameState state;
		static void init();
		static void clean();
};

#endif
