#include <SFML/Graphics.hpp>
#include "scene.hpp"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::add_sprite_ticker(SpriteTicker* sprite_ticker) {
	this->sprite_tickers.push_back(sprite_ticker);
}

void Scene::render(sf::RenderWindow* window) {
	for (auto& sprite_ticker : this->sprite_tickers) {
		window->draw(*sprite_ticker->sprite);
	}
}

void Scene::tick() {
	for (auto& sprite_ticker : sprite_tickers) {
		sprite_ticker->tick();
	}
}
