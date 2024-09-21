#include <string>
#include <iostream>

#include "../objects/event.hpp"
#include "../util/texture.hpp"
#include "../util/font.hpp"

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

class ScoreTextTicker : public SpriteTicker {
	public:
		ScoreTextTicker() {
			this->font = new sf::Font();
			load_font(this->font, "fonts/DepartureMono-Regular.otf");
			
			sf::Text* text = new sf::Text();
			text->setFont(*font);
			text->setString(std::to_string(score));
			text->setCharacterSize(26);
			text->setFillColor(sf::Color::White);

			sf::FloatRect textBounds = text->getLocalBounds();
			text->setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

			this->sprite = text;
			this->texture_ptr = nullptr;
		}

		~ScoreTextTicker() override {
			std::cout << "dropping font" << std::endl;
			if (this->font != nullptr)
				delete font;
			font = nullptr;
			std::cout << "dropped" << std::endl;
		}

	private:
		sf::Font* font;
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

	ScoreTextTicker* score = new ScoreTextTicker();
	sf::Text* s_s = dynamic_cast<sf::Text*>(score->sprite);
	
	s_s->setPosition(sf::Vector2f(300, 500));

	this->add_sprite_ticker(score);
}

void GameOverScene::event_handler(sf::Event* event) {
}
