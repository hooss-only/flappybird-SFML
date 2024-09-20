#include "physics.hpp"

PhysicalObject::PhysicalObject() {
	this->velocity.x = 0;
	this->velocity.y = 0;
}

PhysicalObject::~PhysicalObject () {}

void PhysicalObject::apply_velocity(sf::Sprite* sprite) {
	sprite->move(this->velocity);
}

void PhysicalObject::gravity_calculation() {
	this->velocity.y -= gravity;
}

void PhysicalObject::set_gravity(float gravity) {
	this->gravity = gravity;
}

sf::Vector2f PhysicalObject::get_velocity() {
	return this->velocity;
}
