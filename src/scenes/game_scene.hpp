#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

#include "../objects/scene.hpp"
#include "../objects/sprite.hpp"
#include "../objects/physics.hpp"

class FlappyBirdTicker : public SpriteTicker, PhysicalObject {
	public:
		FlappyBirdTicker();
		~FlappyBirdTicker() override;
		
		void jump();
		void tick() override;

		bool dead;
	
	private:
		void change_angle_by_y_velocity();
};

struct Ray {
	sf::Vector2f origin;
	sf::Vector2f direction;
	bool tickable;
};

class LiveScoreTextTicker : public SpriteTicker {
	public:
		LiveScoreTextTicker();
		~LiveScoreTextTicker() override;

		void tick() override;
};

class StartCountDownTicker : public SpriteTicker {
	public:
		StartCountDownTicker();
		~StartCountDownTicker() override;

		void tick() override;
};

class BackgroundTicker : public SpriteTicker {
	public:
		BackgroundTicker();
		~BackgroundTicker() override;

		void tick() override;
		
};

class GroundTicker : public SpriteTicker {
	public:
		GroundTicker();
		~GroundTicker() override;

		void tick() override;
};

class GameScene : public Scene {
	public:
		GameScene();
		~GameScene() override;
		
		void init() override;
		void event_handler(sf::Event* event) override;
	
	private:
		void add_ray(float x);
		void add_pipe_set(float y);

		void handle_key(sf::Event& event);
		void check_get_point(sf::Sprite& player_sprite);
		void check_player_touched_floor(sf::Sprite& player_sprite);
		void check_player_touched_pipe(sf::Sprite& player_sprite);

		unsigned int count;
	
		std::vector<Ray*> rays;
		std::mt19937 gen;
		std::uniform_real_distribution<> dis;
		sf::Clock clock;
		bool player_jumping;
		FlappyBirdTicker* player;
		LiveScoreTextTicker* score_text;
		StartCountDownTicker* start_count_text;

		BackgroundTicker* background1;
		BackgroundTicker* background2;
		BackgroundTicker* background3;

		GroundTicker* ground1;
		GroundTicker* ground2;

		sf::Sound player_hit_sound;
		sf::Sound player_die_sound;
		sf::Sound point_sound;

		sf::SoundBuffer player_hit_sound_buff;
		sf::SoundBuffer player_die_sound_buff;
		sf::SoundBuffer point_sound_buff;
};

#endif
