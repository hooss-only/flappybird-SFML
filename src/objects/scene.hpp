#ifndef SCENE_HPP
#define SCENE_HPP

#include "sprite.hpp"
#include <vector>

class Scene {
	public:
		Scene();
		virtual ~Scene();
		
		void add_sprite_ticker(SpriteTicker* sprite);
		void tick();
		void render(sf::RenderWindow* window);
	
	private:
		std::vector<SpriteTicker*> sprite_tickers;
};

class SceneManager {
	public:
		SceneManager();
		virtual ~SceneManager();

		void set_scene(Scene* scene);

	private:
		Scene *current_scene;
};

#endif
