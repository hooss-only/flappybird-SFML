#include "../util/texture.hpp"

#include "game_over_scene.hpp"

class GameOverSpriteTicker : public SpriteTicker {
	public:
		GameOverSpriteTicker() {
			sf::Texture* texture = new sf::Texture();
			load_texture(texture, "sprites/gameover.png");

			sf::Sprite* sprite = new sf::Sprite();
			sprite->setTexture(*texture);

			sprite->setScale(sf::Vector2f(2.f, 2.f));

			this->sprite = sprite;
			this->texture_ptr = texture;
		}

		~GameOverSpriteTicker() override {}
};

ButtonSpriteTicker::ButtonSpriteTicker() {}
ButtonSpriteTicker::~ButtonSpriteTicker() {}

void ButtonSpriteTicker::tick() {};

GameOverScene::GameOverScene() {
	GameOverSpriteTicker* game_over = new GameOverSpriteTicker();
	game_over->sprite->setPosition(sf::Vector2f(100, 200));
	this->add_sprite_ticker(game_over);
}
GameOverScene::~GameOverScene() {}

void GameOverScene::event_handler(sf::Event* event) {}
