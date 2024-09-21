#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <SFML/Graphics.hpp>
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

class GameScene : public Scene {
	public:
		GameScene();
		~GameScene() override;
		
		void event_handler(sf::Event* event) override;

		static unsigned int score;
	
	private:
		void add_ray(float x);
		void add_pipe_set(float y);
	
		std::vector<Ray*> rays;
		std::mt19937 gen;
		std::uniform_real_distribution<> dis;
		sf::Clock clock;
		bool player_jumping;
		FlappyBirdTicker* player;
};

#endif
