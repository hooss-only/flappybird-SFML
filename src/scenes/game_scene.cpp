#include <iostream>

#include "../objects/event.hpp"
#include "../util/texture.hpp"
#include "../util/audio.hpp"
#include "../util/font.hpp"

#include "game_scene.hpp"

const float SPEED = 1.0f;
const sf::Vector2f SCALE = sf::Vector2f(2.0f, 2.0f); const float JUMP_POWER = 10.0f;
const float PIPE_INTERVAL = 3.5f;
const float PIPE_GAP = 280.0f;

bool rayIntersectsSprite(const Ray& ray, const sf::Sprite& sprite) {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	
	float tmin = (bounds.left - ray.origin.x) / ray.direction.x;
	float tmax = ((bounds.left + bounds.width) - ray.origin.x) / ray.direction.x;
	
	if (tmin > tmax) std::swap(tmin, tmax);
	
	float tymin = (bounds.top - ray.origin.y) / ray.direction.y;
	float tymax = ((bounds.top + bounds.height) - ray.origin.y) / ray.direction.y;
	
	if (tymin > tymax) std::swap(tymin, tymax);
	
	if ((tmin > tymax) || (tymin > tmax)) return false;
	
	return true;
}

FlappyBirdTicker::FlappyBirdTicker() : SpriteTicker() {
	this->ticking = false;

	sf::Texture* flappy_texture = new sf::Texture();
	load_texture(flappy_texture, "sprites/flappy.png");

	sf::Sprite* flappy_sprite = new sf::Sprite();
	flappy_sprite->setTexture(*flappy_texture);

	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(flappy_sprite);

	this->sprite = flappy_sprite;
	this->texture_ptr = flappy_texture;

	sprite->setPosition(200, 400);
	sprite->setScale(SCALE);
	this->set_gravity(0.3f);
	sprite->setOrigin(15, 15);
}

FlappyBirdTicker::~FlappyBirdTicker() {}

void FlappyBirdTicker::jump() {
	this->set_velocity(this->get_velocity().x, -1 * JUMP_POWER);
}

void FlappyBirdTicker::change_angle_by_y_velocity() {
	float velocity_y = this->get_velocity().y;
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
	sprite->setRotation(velocity_y*3);
}

void FlappyBirdTicker::tick() {
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
	this->gravity_calculation();
	if (sprite->getPosition().y > 1000 || sprite->getPosition().y < 0) {
		this->dead = true;
		if (sprite->getPosition().y < 0) {
			this->set_velocity(0, 1);
			
		}
	}
  this->apply_velocity(sprite);
	this->change_angle_by_y_velocity();
}

class PipeTicker : public SpriteTicker {
	public:
		PipeTicker() : SpriteTicker() {
			sf::Texture* pipe_texture = new sf::Texture();
			load_texture(pipe_texture, "sprites/pipe-green.png");

			sf::Sprite* pipe_sprite = new sf::Sprite();
			pipe_sprite->setTexture(*pipe_texture);

			this->sprite = pipe_sprite;
			this->texture_ptr = pipe_texture;

			sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
			sprite->setPosition(700, 400);
			sprite->setOrigin(26, 0);
			sprite->setScale(SCALE);
		}
		~PipeTicker() override {};


		void tick() override {
			if (!this->ticking) return;

			sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
			sprite->move(-1.0f * SPEED, 0);
		}
};


LiveScoreTextTicker::LiveScoreTextTicker() {
	sf::Text* text = new sf::Text();
	text->setFont(*game_font);
	text->setString(std::to_string(score));
	text->setCharacterSize(26);
	text->setFillColor(sf::Color::White);

	sf::FloatRect textBounds = text->getLocalBounds();
	text->setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

	text->setPosition(300, 20);
	
	this->sprite = text;
	this->texture_ptr = nullptr;
}

LiveScoreTextTicker::~LiveScoreTextTicker() {}

void LiveScoreTextTicker::tick() {}

StartCountDownTicker::StartCountDownTicker() {
	sf::Text* text = new sf::Text();
	text->setFont(*game_font);
	text->setCharacterSize(26);
	text->setFillColor(sf::Color::White);

	sf::FloatRect textBounds = text->getLocalBounds();
	text->setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

	text->setPosition(300, 400);
	
	this->sprite = text;
	this->texture_ptr = nullptr;
}

StartCountDownTicker::~StartCountDownTicker() {}

void StartCountDownTicker::tick() {}

GameScene::GameScene() {}

GameScene::~GameScene() {
	for (Ray* ray : this->rays) {
		if (ray == nullptr) continue;
		delete ray;
		ray = nullptr;
	}
}

void GameScene::init() {
	score = 0;
	this->count = 3;

	FlappyBirdTicker* flappy_ticker = new FlappyBirdTicker();
	this->player = flappy_ticker;
	this->player->depth = 1;
	this->player->dead = false;
	this->add_sprite_ticker(flappy_ticker);
	this->player_jumping = false;

	load_audio(&this->player_hit_sound_buff, "sounds/hit.wav");
	load_audio(&this->player_die_sound_buff, "sounds/die.wav");
	load_audio(&this->point_sound_buff, "sounds/point.wav");
	
	player_hit_sound.setBuffer(player_hit_sound_buff);
	player_die_sound.setBuffer(player_die_sound_buff);
	point_sound.setBuffer(point_sound_buff);

	this->clock.restart();

	LiveScoreTextTicker* score_text = new LiveScoreTextTicker();
	this->score_text = score_text;
	this->score_text->depth = 2;
	this->add_sprite_ticker(score_text);

	StartCountDownTicker* start_count_text = new StartCountDownTicker();
	this->start_count_text = start_count_text;
	this->start_count_text->depth = 2;

	sf::Text* count_text = dynamic_cast<sf::Text*>(this->start_count_text->sprite);
	count_text->setString(std::to_string(this->count));

	this->add_sprite_ticker(start_count_text);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(400.0f, 800.0f);

	this->gen = gen;
	this->dis = dis;
}

void GameScene::add_ray(float x) {
	Ray* ray = new Ray();
	ray->origin = sf::Vector2f(x, 0.f);
	ray->direction = sf::Vector2f(0.f, 1.f);
	ray->tickable = true;

	rays.push_back(ray);
}

void GameScene::add_pipe_set(float y) {
		PipeTicker* pipe_ticker = new PipeTicker();
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(pipe_ticker->sprite);
		sprite->setPosition(sprite->getPosition().x, y);

		this->add_ray(sprite->getPosition().x);

		this->add_sprite_ticker(pipe_ticker);

		PipeTicker* pipe_ticker_pair = new PipeTicker();
		sf::Sprite* sprite_pair = dynamic_cast<sf::Sprite*>(pipe_ticker_pair->sprite);
		sprite_pair->setRotation(180);
		sprite_pair->setPosition(sprite->getPosition().x, sprite->getPosition().y - PIPE_GAP);

		this->add_sprite_ticker(pipe_ticker_pair);
}

void GameScene::event_handler(sf::Event* event) {
	sf::Sprite* player_sprite = dynamic_cast<sf::Sprite*>(this->player->sprite);
	
	if (player_sprite->getPosition().y < 0) {
		this->player_hit_sound.play();
		this->player_die_sound.play();
	}

	if (!player->dead && player_sprite->getPosition().y > 1000) {
		this->player_die_sound.play();
	}

	if (this->clock.getElapsedTime().asSeconds() >= 1 && count > 0) {
		count--;
		sf::Text* text = dynamic_cast<sf::Text*>(this->start_count_text->sprite);
		text->setString(std::to_string(this->count));
		if (count == 0) {
			this->player->ticking = true;
			this->start_count_text->visible = false;
		}
		clock.restart();
	}

	if (this->clock.getElapsedTime().asSeconds() >= PIPE_INTERVAL && !this->player->dead) {
		// 400 ~ 800
		this->add_pipe_set(this->dis(this->gen));
		clock.restart();
	}
	
	for (SpriteTicker* sprite_ticker: this->sprite_tickers) {
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(sprite_ticker->sprite);

		if (!sprite)
			continue;

		if (sprite->getPosition().x <= -100) {
			sprite_ticker->visible = false;
			sprite_ticker->ticking = false;
		}

		if (sprite_ticker != this->player && sprite_ticker->visible && !this->player->dead) {
			if (player_sprite->getGlobalBounds().intersects(sprite->getGlobalBounds())) {
				this->player->dead = true;
				player_hit_sound.play();
				player_die_sound.play();
				for (SpriteTicker* sprite_ticker: this->sprite_tickers) {
					if (sprite_ticker != this->player && sprite_ticker->visible) sprite_ticker->ticking = false;
				}
				this->clock.restart();
			}
		}
	}

	if (!player->dead) {
		for (Ray* ray : this->rays) {
			if (ray == nullptr || !ray->tickable) continue;
			ray->origin.x -= SPEED;
			if (ray->origin.x <= -100) ray->tickable = false;

			if (rayIntersectsSprite(*ray, *player_sprite)) {
				point_sound.play();
				score++;
				sf::Text* s_t = dynamic_cast<sf::Text*>(score_text->sprite);

				s_t->setString(std::to_string(score));

				std::cout<<score<<std::endl;
				ray->tickable = false;
			}
		}
	}

	if (this->player->dead && this->clock.getElapsedTime().asSeconds() >= 3.0f) 
		state = "player_dead";

	if (event->type == sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Up && this->player->ticking && !this->player_jumping && !this->player->dead) {
				this->player->jump();
				this->player_jumping = true;
			} }
	if (event->type == sf::Event::KeyReleased) {
		if (event->key.code == sf::Keyboard::Up && this->player->ticking && this->player_jumping && !this->player->dead) {
				this->player_jumping = false;
			}
	}
}
