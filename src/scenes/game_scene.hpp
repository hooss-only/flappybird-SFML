#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <SFML/Graphics.hpp>

#include "../objects/scene.hpp"
#include "../objects/sprite.hpp"

class FlappyBirdTicker : public SpriteTicker {
	public:
		FlappyBirdTicker();
		~FlappyBirdTicker();

		void tick() override;
};

class GameScene : public Scene {
	public:
		GameScene();
		~GameScene();

		void init() override;
};

#endif
