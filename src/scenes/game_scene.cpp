#include "../util/texture.hpp"
#include "../util/audio.hpp"
#include "../util/font.hpp"
#include "../game.hpp"

#include "game_scene.hpp"

const float SPEED = 2.f;
const sf::Vector2f SCALE = sf::Vector2f(2.0f, 2.0f); 
const float JUMP_POWER = 10.0f;
const float PIPE_INTERVAL = 3.f;
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
	if (sprite->getPosition().y > 780 || sprite->getPosition().y < 0) {
		this->dead = true;
		if (sprite->getPosition().y < 0) {
			this->set_velocity(0, 1);
		} else if (sprite->getPosition().y > 780) {
			this->set_velocity(0, 0);
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
	text->setString(std::to_string(Game::score));
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

BackgroundTicker::BackgroundTicker() {
	sf::Sprite* sprite = new sf::Sprite;
	
	sf::Texture* texture = new sf::Texture();
	load_texture(texture, "sprites/background-day.png");
	sprite->setTexture(*texture);

	sprite->setPosition(0, 0);
	sprite->setScale(2.f, 2.f);

	this->sprite = sprite;
	this->texture_ptr = texture;
}

BackgroundTicker::~BackgroundTicker() {}

void BackgroundTicker::tick() {
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
	sprite->move(-SPEED/3, 0);

	if (sprite->getPosition().x <= -555) {
		sprite->setPosition(555*2, 0);
	}
}

GroundTicker::GroundTicker() {
	this->depth = 2;
	sf::Sprite* sprite = new sf::Sprite();

	sf::Texture* texture = new sf::Texture();
	load_texture(texture, "sprites/base.png");
	sprite->setTexture(*texture);
	
	sprite->setPosition(0, 800);
	sprite->setScale(2.f, 2.f);

	this->sprite = sprite;
	this->texture_ptr = texture;
}

GroundTicker::~GroundTicker() {}

void GroundTicker::tick() {
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(this->sprite);
	sprite->move(-SPEED, 0);

	if (sprite->getPosition().x <= -672) {
		sprite->setPosition(672, 800);
	}
}

GameScene::GameScene() {}

GameScene::~GameScene() {
	for (Ray* ray : this->rays) {
		if (ray == nullptr) continue;
		delete ray;
		ray = nullptr;
		this->rays.clear();
	}
}

void GameScene::init() {
	Game::score = 0;
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

	BackgroundTicker* background1 = new BackgroundTicker();
	this->add_sprite_ticker(background1);
	this->background1 = background1;

	BackgroundTicker* background2 = new BackgroundTicker();
	sf::Sprite* b2_sprite = dynamic_cast<sf::Sprite*>(background2->sprite);
	b2_sprite->setPosition(555, 0);
	this->add_sprite_ticker(background2);
	this->background2 = background2;

	BackgroundTicker* background3 = new BackgroundTicker();
	sf::Sprite* b3_sprite = dynamic_cast<sf::Sprite*>(background3->sprite);
	b3_sprite->setPosition(555 * 2, 0);
	this->add_sprite_ticker(background3);
	this->background3 = background3;

	GroundTicker* ground1 = new GroundTicker();
	this->add_sprite_ticker(ground1);
	this->ground1 = ground1;

	GroundTicker* ground2 = new GroundTicker();
	sf::Sprite* g2_sprite = dynamic_cast<sf::Sprite*>(ground2->sprite);
	g2_sprite->setPosition(672, 800);
	this->add_sprite_ticker(ground2);
	this->ground2 = ground2;

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
	
	if (!player->dead && (player_sprite->getPosition().y < 0 || player_sprite->getPosition().y > 780)) {
		check_player_touched_floor(*player_sprite);
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
	
	check_player_touched_pipe(*player_sprite);

	if (!player->dead) check_get_point(*player_sprite);

	handle_key(*event);
}

void GameScene::check_player_touched_pipe(sf::Sprite& player_sprite) {
	for (SpriteTicker* sprite_ticker: this->sprite_tickers) {
		if (sprite_ticker == nullptr) continue;
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(sprite_ticker->sprite);

		if (!sprite)
			continue;

		if (sprite_ticker != background1 && sprite_ticker != background2 && sprite_ticker != background3 && sprite_ticker != ground1 && sprite_ticker != ground2 && sprite->getPosition().x <= -100) {
			sprite_ticker->visible = false;
			sprite_ticker->ticking = false;
			this->sprite_tickers.erase(std::remove(this->sprite_tickers.begin(), this->sprite_tickers.end(), sprite_ticker), sprite_tickers.end());
			delete sprite_ticker;
			sprite_ticker = nullptr;
			break;
		}

		if (sprite_ticker != this->player && sprite_ticker != this->background1 && sprite_ticker != this->background2 && sprite_ticker != this->background3 && sprite_ticker != this->ground1 && sprite_ticker != this->ground2 && sprite_ticker->visible && !this->player->dead) {
			if (player_sprite.getGlobalBounds().intersects(sprite->getGlobalBounds())) {
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
}

void GameScene::check_player_touched_floor(sf::Sprite& player_sprite) {
	background1->ticking = false;
	background2->ticking = false;
	background3->ticking = false;
	ground1->ticking = false;
	ground2->ticking = false;
	this->player_hit_sound.play();
	if (player_sprite.getPosition().y < 0) this->player_die_sound.play();
}

void GameScene::check_get_point(sf::Sprite& player_sprite) {
	for (Ray* ray : this->rays) {
		if (ray == nullptr || !ray->tickable) continue;
		ray->origin.x -= SPEED;
		if (ray->origin.x <= -100) ray->tickable = false;

		if (rayIntersectsSprite(*ray, player_sprite)) {
			point_sound.play();
			Game::score++;
			sf::Text* s_t = dynamic_cast<sf::Text*>(score_text->sprite);

			s_t->setString(std::to_string(Game::score));

			ray->tickable = false;
		}
	}
}

void GameScene::handle_key(sf::Event& event) {
	if (this->player->dead && this->clock.getElapsedTime().asSeconds() >= 3.0f) 
		Game::state = GameState::PLAYER_DEAD;

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up && this->player->ticking && !this->player_jumping && !this->player->dead) {
			this->player->jump();
			this->player_jumping = true;
		} 
	}

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Up && this->player->ticking && this->player_jumping && !this->player->dead) {
			this->player_jumping = false;
		}
	}
}
