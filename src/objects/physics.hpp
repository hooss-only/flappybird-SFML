#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <SFML/Graphics.hpp>

class PhysicalObject {
	public:
		PhysicalObject();
		~PhysicalObject();
		
		void apply_velocity(sf::Sprite* sprite);
		void gravity_calculation();
		void set_gravity(float gravity);
		sf::Vector2f get_velocity();

	private:
		sf::Vector2f velocity;
		float gravity;
};

#endif
