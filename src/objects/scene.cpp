#include <SFML/Graphics.hpp>
#include <iostream>
#include "scene.hpp"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::add_sprite_ticker(SpriteTicker* sprite_ticker) {
	this->sprite_tickers.push_back(sprite_ticker);
}

void Scene::render(sf::RenderWindow* window) {
	for (SpriteTicker* sprite_ticker : this->sprite_tickers) {
		if (sprite_ticker == nullptr || sprite_ticker->sprite == nullptr || !sprite_ticker->visible) continue;
		window->draw(*sprite_ticker->sprite); 
	}
}

void Scene::tick() {
	for (auto& sprite_ticker : sprite_tickers) {
		sprite_ticker->tick();
	}
}

void Scene::event_handler(sf::Event* event) {}

void Scene::drop() {
	for (auto& sprite_ticker : sprite_tickers) {
		if (sprite_ticker == nullptr) continue;
		std::cout << "dropping a sprite_ticker of scene" << std::endl;
		delete sprite_ticker;
		sprite_ticker = nullptr;
		std::cout << "dropped a sprite_ticker" << std::endl;
	}
}

SceneManager::SceneManager() {}
SceneManager::~SceneManager() {}

void SceneManager::render(sf::RenderWindow* window) {
	if (this->current_scene == nullptr) return;
	this->current_scene->render(window);
}

void SceneManager::set_scene(Scene* scene) {
	this->current_scene = scene;
}

void SceneManager::change_scene(Scene* scene) {
	delete this->current_scene;
	this->current_scene = scene;
}

void SceneManager::tick() {
	if (this->current_scene == nullptr) return;
	this->current_scene->tick();
}

void SceneManager::event_handler(sf::Event* event) {
	if (this->current_scene == nullptr) return;
	this->current_scene->event_handler(event);

}

void SceneManager::end_game() {
	if (this->current_scene != nullptr)
		current_scene->drop();
	current_scene = nullptr;
}
