#include <string>
#include <iostream>

#include "../objects/event.hpp"
#include "../util/texture.hpp"
#include "../util/font.hpp"

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
			std::cout << "constructor of text called." << std::endl;

			sf::Text* text = new sf::Text();
			text->setFont(*game_font);
			text->setString(std::to_string(score));
			text->setCharacterSize(26);
			text->setFillColor(sf::Color::White);
			std::cout << "made a text" << std::endl;

			sf::FloatRect textBounds = text->getLocalBounds();
			text->setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

			this->sprite = text;
			this->texture_ptr = nullptr; 
		}

		~ScoreTextTicker() override {
		}
};

ButtonSpriteTicker::ButtonSpriteTicker() {}
ButtonSpriteTicker::~ButtonSpriteTicker() {}

void ButtonSpriteTicker::tick() {};

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() {}

void GameOverScene::init() {
	std::cout << "Game Over! Score: " << score << std::endl;
	GameOverSpriteTicker* game_over = new GameOverSpriteTicker();
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(game_over->sprite);
	sprite->setPosition(sf::Vector2f(100, 200));
	this->add_sprite_ticker(game_over);

	ScoreTextTicker* score_ticker = new ScoreTextTicker();
	std::cout << score_ticker << std::endl;
	sf::Text* s_s = dynamic_cast<sf::Text*>(score_ticker->sprite);
	std::cout << s_s << std::endl;
	
	if (s_s) 
		s_s->setPosition(sf::Vector2f(300, 500));

	this->add_sprite_ticker(score_ticker);
}

void GameOverScene::event_handler(sf::Event* event) {
}
