#ifndef GAME_OVER_SCENE_HPP
#define GAME_OVER_SCENE_HPP

#include "../objects/scene.hpp"

class ButtonSpriteTicker : public SpriteTicker {
	public:
		ButtonSpriteTicker();
		~ButtonSpriteTicker() override;
		
		void clicked();
		void hovered();
		void tick() override;
};

class GameOverScene : public Scene {
	public:
		GameOverScene();
		~GameOverScene() override;

		void event_handler(sf::Event* event) override;
};

#endif
