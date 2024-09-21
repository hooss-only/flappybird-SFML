#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <iostream>

#include "resource.hpp"

void load_audio(sf::SoundBuffer* sound_buffer, std::string sound_path) {
	sound_path = get_resource_dir() + sound_path;
	if (!sound_buffer->loadFromFile(sound_path)) {
		std::cerr << "Error Loading " << sound_path << std::endl;
		exit(1);
	}
}
