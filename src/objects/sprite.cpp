#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprite.hpp"

SpriteTicker::SpriteTicker() {
	this->depth = 0;
	this->sprite = nullptr;
	this->texture_ptr = nullptr;
	this->visible = true;
	this->ticking = true;
}
SpriteTicker::~SpriteTicker() {
	std::cout << "dropping sprite_ticker elements" << std::endl;
	this->drop();
	std::cout << "dropped elements" << std::endl;
}
void SpriteTicker::tick() {}

void SpriteTicker::drop() {
	if (this-> sprite != nullptr)
		delete this->sprite;
	if (this->texture_ptr != nullptr)
		delete this->texture_ptr;
	this->sprite = nullptr;
	this->texture_ptr = nullptr;
}
