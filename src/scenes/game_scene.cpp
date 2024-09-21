#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

#include "../objects/event.hpp"
#include "../util/texture.hpp"

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
	sf::Texture* flappy_texture = new sf::Texture();
	load_texture(flappy_texture, "sprites/flappy.png");

	sf::Sprite* flappy_sprite = new sf::Sprite();
	flappy_sprite->setTexture(*flappy_texture);

	this->sprite = flappy_sprite;
	this->texture_ptr = flappy_texture;

	this->sprite->setPosition(200, 0);
	this->sprite->setScale(SCALE);
	this->set_gravity(0.3f);
	this->sprite->setOrigin(15, 15);
}
FlappyBirdTicker::~FlappyBirdTicker() {}

void FlappyBirdTicker::jump() {
	this->set_velocity(this->get_velocity().x, -1 * JUMP_POWER);
}

void FlappyBirdTicker::change_angle_by_y_velocity() {
	float velocity_y = this->get_velocity().y;
	this->sprite->setRotation(velocity_y*3);
}

void FlappyBirdTicker::tick() {
	this->gravity_calculation();
	if (this->sprite->getPosition().y > 1100) this->set_velocity(0, -1);
  this->apply_velocity(this->sprite);
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

			this->sprite->setPosition(700, 400);
			this->sprite->setOrigin(26, 0);
			this->sprite->setScale(SCALE);
		}
		~PipeTicker() override {};


		void tick() override {
			if (!this->ticking) return;
			this->sprite->move(-1.0f * SPEED, 0);
		}
};

GameScene::GameScene() {
	this->score = 0;

	FlappyBirdTicker* flappy_ticker = new FlappyBirdTicker();
	this->player = flappy_ticker;
	this->player->dead = false;
	this->add_sprite_ticker(flappy_ticker);
	this->player_jumping = false;

	this->clock.restart();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(400.0f, 800.0f);

	this->gen = gen;
	this->dis = dis;
}

GameScene::~GameScene() {
	for (Ray* ray : this->rays) {
		if (ray == nullptr) continue;
		delete ray;
		ray = nullptr;
	}
}

unsigned int GameScene::score = 0;

void GameScene::add_ray(float x) {
	Ray* ray = new Ray();
	ray->origin = sf::Vector2f(x, 0.f);
	ray->direction = sf::Vector2f(0.f, 1.f);
	ray->tickable = true;

	rays.push_back(ray);
}

void GameScene::add_pipe_set(float y) {
		PipeTicker* pipe_ticker = new PipeTicker();
		pipe_ticker->sprite->setPosition(pipe_ticker->sprite->getPosition().x, y);

		this->add_ray(pipe_ticker->sprite->getPosition().x);

		this->add_sprite_ticker(pipe_ticker);

		PipeTicker* pipe_ticker_pair = new PipeTicker();
		pipe_ticker_pair->sprite->setRotation(180);
		pipe_ticker_pair->sprite->setPosition(pipe_ticker->sprite->getPosition().x, pipe_ticker->sprite->getPosition().y - PIPE_GAP);

		this->add_sprite_ticker(pipe_ticker_pair);
}

void GameScene::event_handler(sf::Event* event) {
	if (this->clock.getElapsedTime().asSeconds() >= PIPE_INTERVAL && !this->player->dead) {
		// 400 ~ 800
		this->add_pipe_set(this->dis(this->gen));
		clock.restart();
	}
	
	for (SpriteTicker* sprite_ticker: this->sprite_tickers) {
		if (sprite_ticker->sprite->getPosition().x <= -100) {
			sprite_ticker->visible = false;
			sprite_ticker->ticking = false;
		}

		if (sprite_ticker != this->player && sprite_ticker->visible) {
			if (player->sprite->getGlobalBounds().intersects(sprite_ticker->sprite->getGlobalBounds())) {
				this->player->dead = true;
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

			if (rayIntersectsSprite(*ray, *player->sprite)) {
				this->score++;
				std::cout<<score<<std::endl;
				ray->tickable = false;
			}
		}
	}

	if (this->player->dead && this->clock.getElapsedTime().asSeconds() >= 3.0f) 
		GameEvent::state = "player_dead";

	if (event->type == sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Up && !this->player_jumping && !this->player->dead) {
				this->player->jump();
				this->player_jumping = true;
			} }
	if (event->type == sf::Event::KeyReleased) {
		if (event->key.code == sf::Keyboard::Up && this->player_jumping && !this->player->dead) {
				this->player_jumping = false;
			}
	}
}
