#include "game.hpp"

sf::RenderWindow* Game::window = nullptr;
GameState Game::state = GameState::NONE;
int Game::score = 0;

void Game::init() {
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "FlappyBird");
}

void Game::clean() {
	if (window != nullptr) delete window;
	window = nullptr;
}
