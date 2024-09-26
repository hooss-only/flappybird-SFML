#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "scene.hpp"

Scene::Scene() {}
Scene::~Scene() {}

bool compare_depth(SpriteTicker* a, SpriteTicker* b) {
	if (a == nullptr || b == nullptr) return true;
	return a->depth < b->depth;
}

void Scene::add_sprite_ticker(SpriteTicker* sprite_ticker) {
	this->sprite_tickers.push_back(sprite_ticker);
}

void Scene::render(sf::RenderWindow* window) {
	std::sort(this->sprite_tickers.begin(), this->sprite_tickers.end(), compare_depth);
	for (SpriteTicker* sprite_ticker : this->sprite_tickers) {
		if (sprite_ticker == nullptr) continue;
		if (sprite_ticker->sprite == nullptr) continue;
		if (!sprite_ticker->visible) continue;
		window->draw(*sprite_ticker->sprite); 
	}
}

void Scene::tick() {
	for (auto& sprite_ticker : sprite_tickers) {
		if (sprite_ticker == nullptr) continue;
		if (sprite_ticker->ticking)
			sprite_ticker->tick();
	}
}

void Scene::init() {}

void Scene::event_handler(sf::Event* event) {}

void Scene::drop() {
	for (SpriteTicker* sprite_ticker : sprite_tickers) {
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
	current_scene->init();
}

void SceneManager::change_scene(Scene* scene) {
	current_scene->drop();
	this->current_scene = scene;
	current_scene->init();
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
