#include <SFML/Graphics.hpp>
#include <iostream>
#include "scene.hpp"

Scene::Scene() {}
Scene::~Scene() {}

void Scene::init() {};

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

SceneManager::SceneManager() {}
SceneManager::~SceneManager() {}

void SceneManager::render(sf::RenderWindow* window) {
	std::cout << "rendering scene_ptr: " << current_scene << std::endl;
	if (this->current_scene == nullptr) {
		throw std::runtime_error("current_scene is nullptr!");
	}
	this->current_scene->render(window);
}

void SceneManager::set_scene(Scene* scene) {
	scene->init();
	this->current_scene = scene;
}
