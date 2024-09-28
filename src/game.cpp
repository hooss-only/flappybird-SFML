#include "game.hpp"

sf::RenderWindow* Game::window = nullptr;

void Game::init() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "FlappyBird");
}

void Game::clean() {
	if (window != nullptr) delete window;
	window = nullptr;
}
