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
		virtual void event_handler(sf::Event* event);
	
	private:
		void drop();
	
	protected:
		std::vector<SpriteTicker*> sprite_tickers;
};

class SceneManager {
	public:
		SceneManager();
		~SceneManager();

		void set_scene(Scene* scene);
		void change_scene(Scene* scene);
		void end_game();
		void tick();
		void event_handler(sf::Event* event);
		void render(sf::RenderWindow* window);

	private:
		Scene* current_scene;
};

#endif
