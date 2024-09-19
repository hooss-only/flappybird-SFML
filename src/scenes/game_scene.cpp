#include <SFML/Graphics.hpp>

#include "../objects/sprite.hpp"
#include "../util/texture.hpp"

#include "game_scene.hpp"

void FlappyBirdTicker::tick() {
}


GameScene::GameScene() {}
GameScene::~GameScene() {}

void GameScene::init() {
	sf::Texture* flappy_texture = new sf::Texture;
	load_texture(flappy_texture, "sprites/flappy.png");

	sf::Sprite* flappy_sprite = new sf::Sprite();
	flappy_sprite->setTexture(*flappy_texture);

	SpriteTicker* flappy_ticker = new SpriteTicker(flappy_sprite);

	this->add_sprite_ticker(flappy_ticker);
}
