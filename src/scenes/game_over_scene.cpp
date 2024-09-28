#include <string>
#include <iostream>

#include "../util/texture.hpp"
#include "../util/font.hpp"
#include "../game.hpp"

#include "game_over_scene.hpp"

class GameOverSpriteTicker : public SpriteTicker {
	public:
		GameOverSpriteTicker() : SpriteTicker() {
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

class ScoreTextTicker : public SpriteTicker {
	public:
		ScoreTextTicker() : SpriteTicker() {
			sf::Text* text = new sf::Text();
			text->setFont(*game_font);
			text->setString(std::to_string(Game::score));
			text->setCharacterSize(26);
			text->setFillColor(sf::Color::White);

			sf::FloatRect textBounds = text->getLocalBounds();
			text->setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

			this->sprite = text;
			this->texture_ptr = nullptr; 
		}

		~ScoreTextTicker() override {
		}
};

ButtonSpriteTicker::ButtonSpriteTicker() {
	sf::Sprite* sprite = new sf::Sprite();
	sf::Texture* texture = new sf::Texture();
	load_texture(texture, "sprites/retry.png");
	sprite->setTexture(*texture);
	
	sprite->setScale(3.f, 3.f);

	sf::FloatRect sprite_bounds = sprite->getLocalBounds();
	sprite->setOrigin(sprite_bounds.width / 2.f, sprite_bounds.height / 2.f);
	sprite->setPosition(sf::Vector2f(300, 800));

	this->sprite = sprite;
	this->texture_ptr = texture;
}
ButtonSpriteTicker::~ButtonSpriteTicker() {}

void ButtonSpriteTicker::tick() {
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (sprite->getGlobalBounds().contains(sf::Mouse::getPosition(*Game::window).x, sf::Mouse::getPosition(*Game::window).y)) {
			Game::state = GameState::RESTART;
		}
	}
};

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {}

void GameOverScene::init() {
	std::cout << "Game Over! Score: " << Game::score << std::endl;
	GameOverSpriteTicker* game_over = new GameOverSpriteTicker();
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(game_over->sprite);
	sprite->setPosition(sf::Vector2f(100, 200));
	this->add_sprite_ticker(game_over);

	ScoreTextTicker* score_ticker = new ScoreTextTicker();
	sf::Text* s_s = dynamic_cast<sf::Text*>(score_ticker->sprite);
	if (s_s) 
		s_s->setPosition(sf::Vector2f(300, 500));
	this->add_sprite_ticker(score_ticker);

	ButtonSpriteTicker* button = new ButtonSpriteTicker();
	this->add_sprite_ticker(button);
}

void GameOverScene::event_handler(sf::Event* event) {
}
